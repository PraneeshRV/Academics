# ---------------------------------------------------------------------------
# Base image: minimal Debian slim (small footprint, has bash/wget available
# after we install them). Kubo ships as a static Go binary, so no language
# runtime is required — we just need somewhere to fetch and run it.
# ---------------------------------------------------------------------------
FROM debian:bookworm-slim

# ---------------------------------------------------------------------------
# Metadata
# ---------------------------------------------------------------------------
LABEL maintainer="praneeshrv404@gmail.com"
LABEL description="Standard IPFS (Kubo) node"

# ---------------------------------------------------------------------------
# Which Kubo version to install. Passed as a build ARG so it's easy to bump
# without editing the rest of the file.
# ---------------------------------------------------------------------------
ARG KUBO_VERSION=v0.42.0

# ---------------------------------------------------------------------------
# Install tools needed to download and unpack the Kubo release, then remove
# them from the final layer's apt cache to keep the image small.
# ---------------------------------------------------------------------------
RUN apt-get update && \
    apt-get install -y --no-install-recommends wget ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# ---------------------------------------------------------------------------
# Download and install the official Kubo (go-ipfs) binary for linux-amd64.
# ---------------------------------------------------------------------------
RUN wget -q "https://dist.ipfs.tech/kubo/${KUBO_VERSION}/kubo_${KUBO_VERSION}_linux-amd64.tar.gz" -O /tmp/kubo.tar.gz && \
    tar -xzf /tmp/kubo.tar.gz -C /tmp && \
    bash /tmp/kubo/install.sh && \
    rm -rf /tmp/kubo /tmp/kubo.tar.gz

# ---------------------------------------------------------------------------
# IPFS repo location. This is where node keys, config, and blockstore data
# live. Declared as a VOLUME so the repo can persist across container restarts.
# ---------------------------------------------------------------------------
ENV IPFS_PATH=/data/ipfs
VOLUME ["/data/ipfs"]

# ---------------------------------------------------------------------------
# Copy in the startup script that initializes the repo (first run only) and
# configures the daemon to listen on all interfaces before starting it.
# ---------------------------------------------------------------------------
COPY start-ipfs.sh /usr/local/bin/start-ipfs.sh
RUN chmod +x /usr/local/bin/start-ipfs.sh

# ---------------------------------------------------------------------------
# Expose the standard IPFS ports:
#   4001 - Swarm (P2P) - talks to other IPFS nodes
#   5001 - API - the RPC/control API and Web UI
#   8080 - Gateway - HTTP access to IPFS content (http://host:8080/ipfs/<cid>)
# ---------------------------------------------------------------------------
EXPOSE 4001 5001 8080

# ---------------------------------------------------------------------------
# Start the node
# ---------------------------------------------------------------------------
ENTRYPOINT ["start-ipfs.sh"]
