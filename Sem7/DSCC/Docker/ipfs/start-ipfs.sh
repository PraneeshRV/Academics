#!/bin/bash
# ---------------------------------------------------------------------------
# start-ipfs.sh
#
# Initializes the IPFS repository the first time the container runs (skips
# it on subsequent runs if a repo already exists in the mounted volume), then
# reconfigures the API and Gateway to listen on 0.0.0.0 so they're reachable
# from outside the container, and finally starts the daemon in the foreground.
# ---------------------------------------------------------------------------
set -e

if [ ! -f "$IPFS_PATH/config" ]; then
    echo "No existing IPFS repo found at $IPFS_PATH — initializing a new one..."
    ipfs init
else
    echo "Existing IPFS repo found at $IPFS_PATH — skipping init."
fi

# By default Kubo binds the API and Gateway to 127.0.0.1, which is only
# reachable from inside the container. Rebind them to 0.0.0.0 so the ports
# published with `docker run -p` actually work.
ipfs config Addresses.API /ip4/0.0.0.0/tcp/5001
ipfs config Addresses.Gateway /ip4/0.0.0.0/tcp/8080

# Allow the Web UI (served from the API port) to be accessed cross-origin,
# useful when hitting it from a browser on the host.
ipfs config --json API.HTTPHeaders.Access-Control-Allow-Origin '["*"]'
ipfs config --json API.HTTPHeaders.Access-Control-Allow-Methods '["GET", "POST", "PUT"]'

echo "Starting IPFS daemon..."
exec ipfs daemon --migrate=true
