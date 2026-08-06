# DSCC Docker Viva — cheatsheet

Docker Hub account: **shadoweternity** · everything below is built, tagged and verified working.

## Folder = image name

Every buildable folder is named after the image it produces, so `docker images` and `ls` line up.

| Folder | Image | Was |
|---|---|---|
| `firstdockerimage/` | `shadoweternity/firstdockerimage:latest` | Lab1.5 |
| `portdockerimage/` | `shadoweternity/portdockerimage:latest` | Class2 |
| `flaskappdockerimage/` | `shadoweternity/flaskappdockerimage:latest` | Lab2/DockerLab1 |
| `filesharingdockerimage/` | `shadoweternity/filesharingdockerimage:2.0` | Lab2/filesharingdockerv2 |
| `filesharingdockerimage-v1/` | `shadoweternity/filesharingdockerimage:1.0` and `:latest` | Lab2/filesharingdocker |
| `loggendockerimage/` | `shadoweternity/loggendockerimage:latest` | Lab3/logger-docker-lab |
| `db-conn-dockerimage/` | `shadoweternity/db-conn-dockerimage:latest` | Lab4 |
| `ipfsdockerimage/` | `shadoweternity/ipfsdockerimage:latest` | ipfs |
| `Lab1-ubuntu-base/` | *(no image built — `FROM ubuntu` only)* | Lab1 |
| `Lab3-compose-website/` | *(no image — compose + bind mount + named volume lab, runs `portdockerimage`)* | Lab3 |

## 0. Bring everything up at once

Compose (one command, all labs):

```bash
cd ~/Praneesh/Academics/Sem7/DSCC/Docker
docker compose -f docker-compose.all.yml up -d --build
docker compose -f docker-compose.all.yml ps
```

Pure CLI (if the evaluator asks for `docker run`, not compose):

```bash
cd ~/Praneesh/Academics/Sem7/DSCC/Docker
./run-all-cli.sh up
./run-all-cli.sh status
```

Tear down:

```bash
docker compose -f docker-compose.all.yml down        # keep volumes
docker compose -f docker-compose.all.yml down -v     # drop volumes too
```

## Port map (no clashes — all run simultaneously)

| Lab | URL | Container port |
|---|---|---|
| PortExpose (portdockerimage) | http://localhost:8081 | 80 |
| Lab 2 — flask app | http://localhost:5000 | 5000 |
| Lab 2 — file sharing | http://localhost:8000 | 8000 |
| Lab 3 — website (bind mount + volume) | http://localhost:8080 | 80 |
| Lab 4 — db connector app | http://localhost:8082 | 8080 |
| Lab 4 — postgres | localhost:5432 | 5432 |
| IPFS gateway | http://127.0.0.1:8083 | 8080 |
| IPFS API + WebUI | http://localhost:5001/webui | 5001 |
| IPFS swarm (P2P) | localhost:4001 | 4001 |

> If a port is "already allocated", an old container from a previous session is still up:
> `docker ps -a` then `docker rm -f <name>`. Named volumes survive that, so no data is lost.

---

## Lab 1 / 1.5 — image layers, ENV, RUN

Source: `firstdockerimage/` · Image: `shadoweternity/firstdockerimage:latest` (busybox base)

```bash
docker run --rm shadoweternity/firstdockerimage sh -c 'echo $HELLO; cat /hello; ls /remove_me'
docker history shadoweternity/firstdockerimage
```

Verified output: `Praneesh` · `world` · `No such file or directory`.

Talking points:
- `HELLO=Praneesh` comes from `ENV` — visible without any `-e` flag.
- `/hello` says `world` — the second `RUN echo world > /hello` overwrote the first layer's content.
- `/remove_me` is gone in the final image, but the layer that created it still exists in
  `docker history`. **Deleting a file in a later layer does not shrink the image** — that is
  why you chain `RUN` commands with `&&` instead of writing many separate `RUN`s.

## PortExpose — EXPOSE vs -p

Source: `portdockerimage/` · Image: `shadoweternity/portdockerimage:latest` (nginx:alpine + custom index.html)

```bash
docker run -d --name portdemo -p 8081:80 shadoweternity/portdockerimage:latest
curl http://localhost:8081          # -> <h1>Hello from Docker!</h1>
docker port portdemo
```

Talking points:
- `EXPOSE 80` in the Dockerfile is **documentation only** — it publishes nothing.
- `-p 8081:80` is what actually maps hostPort:containerPort.
- Left number = host, right = container. Swapping them is the classic mistake.

## Lab 2a — Flask app image

Source: `flaskappdockerimage/` · Image: `shadoweternity/flaskappdockerimage:latest`

```bash
docker build -t shadoweternity/flaskappdockerimage:latest flaskappdockerimage
docker run -d --name flaskdemo -p 5000:5000 shadoweternity/flaskappdockerimage:latest
curl http://localhost:5000                 # -> Welcome to Docker Lab!
docker exec flaskdemo printenv APP_NAME    # -> DSCC-Lab2-flaskappdockerimage
```

Dockerfile covers: base image, `LABEL` maintainer/email, `RUN apt-get` package install,
`ENV`, `WORKDIR`, `COPY`, `pip install`, `EXPOSE 5000`, `CMD`.

## Lab 2b — File sharing service

Source: `filesharingdockerimage/` · Image: `shadoweternity/filesharingdockerimage:2.0`

```bash
docker run -d --name fsdemo -p 8000:8000 shadoweternity/filesharingdockerimage:2.0
curl http://localhost:8000/health     # {"status":"ok","environment":"production",...}
curl http://localhost:8000/files      # {"files":["sample1.txt","sample2.txt","sample3.txt"]}
```

Open http://localhost:8000 and upload a file live — it appears in the list instantly.

Override config through env vars without rebuilding (good demo of `ENV` precedence):

```bash
docker run -d --name fsdemo2 -p 8001:9000 -e APP_PORT=9000 -e APP_ENV=staging \
  shadoweternity/filesharingdockerimage:2.0
curl http://localhost:8001/health      # environment now "staging"
```

Tags on Hub: `1.0`, `2.0`, `latest` — shows image versioning.

## Lab 3a — Compose, bind mount, named volume

Source: `Lab3-compose-website/`

```bash
cd Lab3-compose-website && docker compose up -d
curl http://localhost:8080
```

Live-edit demo (the strongest bind-mount proof):

```bash
echo '<h1>Edited live, no rebuild</h1>' >> Lab3-compose-website/website/index.html
curl http://localhost:8080          # change served immediately
```

- `./website:/usr/share/nginx/html` = **bind mount** — host directory, edits instant, no rebuild.
- `nginx_logs:/var/log/nginx` = **named volume** — Docker-managed, survives `down`.

```bash
docker volume ls
docker run --rm -v dscc-viva_nginx_logs:/l alpine cat /l/access.log
```

## Lab 3b — Named volume persistence

Source: `loggendockerimage/` · Image: `shadoweternity/loggendockerimage:latest`

```bash
docker exec dscc-logger cat /data/log.txt | tail -5
docker restart dscc-logger
docker exec dscc-logger cat /data/log.txt | head -3   # old entries still there
```

The log already carries timestamps from earlier lab sessions (09 Jul, 10 Jul, today) — that
*is* the persistence proof. Without the volume, `log.txt` dies with the container.

## Lab 4 — Multi-container app + PostgreSQL

Source: `db-conn-dockerimage/` · Image: `shadoweternity/db-conn-dockerimage:latest`

```bash
cd db-conn-dockerimage && docker compose up -d
curl http://localhost:8080/health
```

In the all-in-one stack it is on **8082**. Open http://localhost:8082 → sign up → you land on
the dashboard, which proves the app wrote to Postgres and read it back.

```bash
docker exec dscc-db psql -U admin -d mydb -c 'SELECT id, username, created_at FROM users;'
docker logs dscc-dbapp | grep init_db      # -> [init_db] users table ready
```

Talking points:
- The app reaches the DB by **service name** `db` (or container name on a user-defined
  network), not `localhost` — Docker's embedded DNS resolves it.
- `depends_on: condition: service_healthy` + a `pg_isready` healthcheck. Plain `depends_on`
  only waits for the container to *start*, not for Postgres to accept connections — that race
  is exactly what used to make `init_db` fail on first boot.
- All credentials come from environment variables, so the same image runs against any DB.

## IPFS node

Source: `ipfsdockerimage/` · Image: `shadoweternity/ipfsdockerimage:latest` (Debian slim + Kubo v0.42.0)

```bash
docker exec dscc-ipfs ipfs id
docker exec dscc-ipfs ipfs swarm peers | wc -l     # verified: ~189 peers
```

Add a file and fetch it back through the HTTP gateway:

```bash
CID=$(docker exec dscc-ipfs sh -c 'echo "hello from Praneesh DSCC viva" > /tmp/demo.txt && ipfs add -q /tmp/demo.txt')
echo $CID
curl http://127.0.0.1:8083/ipfs/$CID     # -> hello from Praneesh DSCC viva
docker exec dscc-ipfs ipfs cat $CID      # same content, straight from the node
```

Use `127.0.0.1`, not `localhost`, for the gateway: Kubo redirects `localhost` requests to a
per-CID subdomain (`<cid>.ipfs.localhost:8083`), which a browser resolves but `curl` does not.
Worth mentioning — it is origin isolation, a gateway security feature.

Web UI: http://localhost:5001/webui

Talking points:
- Content addressing: the CID is a hash of the content, so identical bytes always give the
  same CID — that is how the network deduplicates and verifies integrity.
- Three ports, three jobs: 4001 peer-to-peer swarm, 5001 control API/WebUI, 8080 (mapped to
  host 8083 here) HTTP gateway.
- `VOLUME /data/ipfs` keeps the node identity (private key) and blockstore across restarts —
  restart the container and `ipfs id` returns the *same* peer ID.

---

## Docker Hub — push / pull

Already logged in as `shadoweternity` (confirm with `docker-credential-desktop list`).

```bash
docker login
docker tag flaskappdockerimage:latest shadoweternity/flaskappdockerimage:latest
docker push shadoweternity/flaskappdockerimage:latest
docker pull shadoweternity/filesharingdockerimage:2.0
```

Prove a pull works from a clean slate:

```bash
docker rmi shadoweternity/portdockerimage:latest
docker pull shadoweternity/portdockerimage:latest
docker run -d -p 8081:80 shadoweternity/portdockerimage:latest
```

## Commands they usually ask for

```bash
docker images                     # local images
docker ps -a                      # containers incl. stopped
docker logs -f dscc-flask         # follow logs
docker exec -it dscc-flask bash   # shell inside a running container
docker inspect dscc-flask         # full JSON: mounts, network, env
docker history <image>            # layer-by-layer build record
docker stats --no-stream          # live resource usage
docker volume ls / docker network ls
docker system df                  # disk used by images/containers/volumes
docker builder prune              # reclaim build cache
```

Definitions worth having ready:
- **Image vs container** — image is the read-only template; container is a running instance
  with a thin writable layer on top.
- **CMD vs ENTRYPOINT** — `CMD` is the default command, fully replaceable by args to
  `docker run`; `ENTRYPOINT` is fixed and `CMD` becomes its arguments.
- **COPY vs ADD** — use `COPY`; `ADD` also auto-extracts tars and fetches URLs, which makes
  builds surprising.
- **Bind mount vs volume** — bind mount points at a host path (dev, live edits); named volume
  is Docker-managed storage for data you want to survive the container.
- **Layer caching** — each instruction is a layer; copy `requirements.txt` and `pip install`
  *before* copying source so a code change does not reinstall dependencies.
