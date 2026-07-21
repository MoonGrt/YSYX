# YSYX Dev Container

This directory provides a Ubuntu 22.04 development environment for YSYX.
It installs Git, GTKWave, Verilator `v5.044-52-g7e7b6d7fb`, SBT, and Mill `0.12.17`.

## Use with VS Code

Open the YSYX repository root in VS Code, then run **Dev Containers: Reopen in
Container**. VS Code uses `.devcontainer/docker-compose.yml` to build the
fixed image `ysyx:latest`, start the fixed container `ysyx-dev`, mount the
repository at `/workspace/YSYX`, and open the terminal there as `root@dev`.

The configuration forwards the WSLg X11 socket, so `gtkwave` can open a window
when VS Code is launched from a WSL distribution with Docker Desktop WSL
integration enabled.

## Build

Run this command from the YSYX repository root:

```bash
docker compose -f .devcontainer/docker-compose.yml build
```

## Run with WSLg GUI support

In a WSL terminal with Docker Desktop WSL integration enabled, run the
following command from the repository root. It bind-mounts the complete
repository. The working directory remains `/workspace/YSYX`. It also forwards
the WSLg X11 socket, so
applications such as GTKWave can open windows on the Windows desktop.

```bash
docker run -it \
  --name ysyx \
  --hostname dev \
  -v "$PWD:/workspace/YSYX" \
  --workdir /workspace/YSYX \
  -e DISPLAY="$DISPLAY" \
  -v /mnt/wslg/.X11-unix:/tmp/.X11-unix \
  ysyx:latest
```

Verify the graphical connection inside the container:

```bash
gtkwave
```

If the WSLg X11 socket is unavailable, update WSL and ensure Docker Desktop's
**Settings > Resources > WSL Integration** enables the Linux distribution in
which the command is run.

## Tool check

```bash
git --version
dpkg-query -W -f='${Version}\n' gtkwave
verilator --version
sbt --version
mill --version
```
