#!/usr/bin/env bash
# DSCC Docker viva — bring every lab up at the same time using ONLY docker CLI
# (no compose). Same host-port map as docker-compose.all.yml.
#
#   ./run-all-cli.sh up      start everything
#   ./run-all-cli.sh down    stop and remove everything (volumes kept)
#   ./run-all-cli.sh status  show what is running + probe every endpoint
#
# Host port map
#   8081 PortExpose | 5000 flask | 8000 filesharing | 8080 Lab3 website
#   8082 Lab4 app   | 5432 postgres | 4001/5001/8083 IPFS

set -euo pipefail
cd "$(dirname "$0")"
ROOT="$PWD"

NET=dscc-net
NAMES=(dscc-lab1 dscc-portexpose dscc-flask dscc-filesharing dscc-lab3web
       dscc-logger dscc-db dscc-dbapp dscc-ipfs)

up() {
  docker network create "$NET" 2>/dev/null || true
  for v in dscc_nginx_logs dscc_logger_data dscc_pgdata dscc_ipfs_data; do
    docker volume create "$v" >/dev/null
  done
  down_quiet

  # Lab 1.5 — layers / ENV / deleted-file proof
  docker run -d --name dscc-lab1 --network "$NET" \
    shadoweternity/firstdockerimage:latest sh -c 'sleep infinity'

  # PortExpose — nginx, host 8081 -> container 80
  docker run -d --name dscc-portexpose --network "$NET" -p 8081:80 \
    shadoweternity/portdockerimage:latest

  # Lab 2a — flask app, host 5000
  docker run -d --name dscc-flask --network "$NET" -p 5000:5000 \
    shadoweternity/flaskappdockerimage:latest

  # Lab 2b — file sharing service, host 8000
  docker run -d --name dscc-filesharing --network "$NET" -p 8000:8000 \
    shadoweternity/filesharingdockerimage:2.0

  # Lab 3a — bind mount (live website) + named volume (nginx logs), host 8080
  docker run -d --name dscc-lab3web --network "$NET" -p 8080:80 \
    -v "$ROOT/Lab3-compose-website/website:/usr/share/nginx/html" \
    -v dscc_nginx_logs:/var/log/nginx \
    shadoweternity/portdockerimage:latest

  # Lab 3b — named volume persistence
  docker run -d --name dscc-logger --network "$NET" \
    -v dscc_logger_data:/data \
    shadoweternity/loggendockerimage:latest

  # Lab 4 — postgres, then the app that talks to it over the docker network
  docker run -d --name dscc-db --network "$NET" -p 5432:5432 \
    -e POSTGRES_USER=admin -e POSTGRES_PASSWORD=secret -e POSTGRES_DB=mydb \
    -v dscc_pgdata:/var/lib/postgresql/data \
    --health-cmd='pg_isready -U admin -d mydb' --health-interval=3s --health-retries=10 \
    postgres:16

  printf 'waiting for postgres to accept connections'
  until [ "$(docker inspect -f '{{.State.Health.Status}}' dscc-db)" = healthy ]; do
    printf '.'; sleep 2
  done; echo ' ready'

  docker run -d --name dscc-dbapp --network "$NET" -p 8082:8080 \
    -e DB_HOST=dscc-db -e DB_PORT=5432 -e DB_USER=admin \
    -e DB_PASSWORD=secret -e DB_NAME=mydb \
    shadoweternity/db-conn-dockerimage:latest

  # IPFS node
  docker run -d --name dscc-ipfs --network "$NET" \
    -p 4001:4001 -p 5001:5001 -p 8083:8080 \
    -v dscc_ipfs_data:/data/ipfs \
    shadoweternity/ipfsdockerimage:latest

  echo; echo "all containers started."; status
}

down_quiet() { docker rm -f "${NAMES[@]}" >/dev/null 2>&1 || true; }

down() {
  down_quiet
  docker network rm "$NET" >/dev/null 2>&1 || true
  echo "stopped and removed. named volumes kept (that is the point of volumes)."
}

probe() { # probe <label> <url>
  printf '  %-34s %s\n' "$1" "$(curl -s -o /dev/null -w 'HTTP %{http_code}' --max-time 5 "$2" || echo UNREACHABLE)"
}

status() {
  echo
  docker ps --filter name=dscc- --format 'table {{.Names}}\t{{.Image}}\t{{.Ports}}\t{{.Status}}'
  echo
  echo "endpoint check:"
  probe "PortExpose   http://localhost:8081" http://localhost:8081/
  probe "Lab2 flask   http://localhost:5000" http://localhost:5000/
  probe "filesharing  http://localhost:8000" http://localhost:8000/
  probe "Lab3 website http://localhost:8080" http://localhost:8080/
  probe "Lab4 app     http://localhost:8082" http://localhost:8082/health
  probe "IPFS gateway http://127.0.0.1:8083" http://127.0.0.1:8083/ipfs/
  printf '  %-34s %s\n' "IPFS API     http://localhost:5001" \
    "$(curl -s -o /dev/null -w 'HTTP %{http_code}' --max-time 5 -X POST http://localhost:5001/api/v0/id || echo UNREACHABLE)"
}

case "${1:-up}" in
  up) up ;;
  down) down ;;
  status) status ;;
  *) echo "usage: $0 [up|down|status]"; exit 1 ;;
esac
