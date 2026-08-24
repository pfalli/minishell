# Minishell deployment

This deployment runs Minishell as the non-root `demo` user and exposes only
ttyd on TCP port 7681. Cloudflare Tunnel should forward
`https://minishell.piero.sbs` to `http://localhost:7681` on the LXC host.

The container does not use privileged mode or host mounts. ttyd is started as:

```sh
ttyd -W -i 0.0.0.0 -p ${PORT:-7681} /app/minishell
```

## Initial deployment

Docker Engine, the Docker Compose plugin, Git, and the repository are expected
to be present in the Debian LXC. From the checked-out repository:

```sh
cd /opt/minishell
chmod +x deploy.sh
./deploy.sh
```

The `chmod` command is needed only once. Confirm locally before configuring or
troubleshooting the Cloudflare Tunnel:

```sh
curl -I http://127.0.0.1:7681
```

## Updates

Future deployments require only:

```sh
cd /opt/minishell
./deploy.sh
```

The script performs a fast-forward-only Git pull, rebuilds and recreates the
service, and prints its final Compose status.

## Operations and debugging

```sh
# Show service status
docker compose ps

# Follow logs
docker compose logs -f --tail=100 minishell

# Rebuild and restart without pulling from Git
docker compose up -d --build

# Inspect the process and confirm it runs as demo
docker compose exec minishell id

# Render and validate the resolved Compose configuration
docker compose config

# Stop and remove the container and Compose network
docker compose down
```

If the container is healthy locally but the public hostname is unavailable,
check the Cloudflare Tunnel service and confirm its origin remains
`http://localhost:7681` (or the LXC address on port 7681, depending on where
`cloudflared` runs).
