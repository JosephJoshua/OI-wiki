This page explains how to deploy an **OI Wiki** environment with Docker.

???+ warning "Warning"
    Run the following steps as root or as a user in the docker group.

## Pull the **OI Wiki** image

```bash
# Run any one of the following commands on the host
# Docker Hub image (official image registry)
docker pull 24oi/oi-wiki
# DaoCloud Hub image (registry in mainland China)
docker pull daocloud.io/sirius/oi-wiki
# Tencent Hub image (registry in mainland China)
docker pull ccr.ccs.tencentyun.com/oi-wiki/oi-wiki
```

## Build the image yourself

```bash
# Run the following commands on the host
# Clone the Git repository
git clone https://github.com/OI-wiki/OI-wiki.git
cd OI-wiki/
# Build the image
docker build -t [name][:tag] . --build-arg [variable1]=[value1] [variable2]=[value2]...
```

-   (Required) Set `[name]` to choose the image name. (Optional) Set `[tag]` to choose the image tag (if you set it, the image name used at run time has both parts).
-   You can set environment variables with the `--build-arg` option.

Available environment variables:

-   Set `WIKI_REPO` to use a mirror of the Wiki repository (GitHub is used if it is not set)
-   Set `PYPI_MIRROR` to use a mirror of PyPI (the official PyPI is used if it is not set)
    -   In mainland China, the TUNA mirror `https://pypi.tuna.tsinghua.edu.cn/simple/` is recommended
-   Set `LISTEN_IP` to change the IP address to listen on (defaults to `0.0.0.0`, which accepts connections on all IPs)
-   Set `LISTEN_PORT` to change the port to listen on (defaults to `8000`)

Example:

```bash
docker build -t OI_Wiki . --build-arg WIKI_REPO=https://hub.fastgit.xyz/OI-wiki/OI-wiki.git PYPI_MIRROR=https://pypi.tuna.tsinghua.edu.cn/simple/
# Builds an image named OI_Wiki (default tag), using FastGit to speed up cloning and the TUNA mirror for PyPI.
```

## Run the container

```bash
# Run the following command on the host
docker run -d -it [image]
```

-   (Required) Set `[image]` to choose the image. For example, the image pulled from Docker Hub is `24oi/oi-wiki`, and the one pulled from DaoCloud Hub is `daocloud.io/sirius/oi-wiki`.
-   (Required) Set `-p [port]:8000` to map the container port to a host port (without it, no port is exposed; replace `[port]` with the host port). Then you can open **OI Wiki** on the host at `http://127.0.0.1:[port]`.
-   Set `--name [name]` to name the container. (Empty by default; replace `[name]` with the container name you want. To see the container ID, run `docker ps`.)

## Use the container

???+ note "Note"
    This example is based on a deployment on Ubuntu latest.

Enter the container:

```bash
# Run the following command on the host
docker exec -it [name] /bin/bash
```

If you drop `-d` from the run command above, you go straight into the container's bash, and the container stops when you exit. With `-d`, the container runs in the background and you need to stop it yourself. The "enter the container" command above is for containers started with `-d`.

Special commands:

```bash
# Run the following commands inside the container
# Update the git repository
wiki-upd

# Use our custom theme
wiki-theme

# Build with mkdocs; the static pages are written to the site folder
wiki-bld

# Build with mkdocs and render MathJax; the static pages are written to the site folder
wiki-bld-math

# Start a server; open http://127.0.0.1:8000 inside the container or http://127.0.0.1:[port] on the host to see the result
wiki-svr

# Fix up the Markdown formatting
wiki-o
```

Exit the container:

```bash
# Run the following commands inside the container
# Exit
exit
```

## Stop the container

```bash
# Run the following command on the host
docker stop [name]
```

## Start the container

```bash
# Run the following command on the host
docker start [name]
```

## Restart the container

```bash
# Run the following command on the host
docker restart [name]
```

## Remove the container

```bash
# Run the following commands on the host
# Stop the container before removing it
docker rm [name]
```

## Update the image

Just run `pull` again. The image is usually not updated, though.

## Remove the image

```bash
# Run the following commands on the host
# Before removing it, first remove any containers built from the oi-wiki image
docker rmi [image]
```

## Questions

If you have any questions, feel free to open an [issue](https://github.com/OI-wiki/OI-wiki/issues/new/choose)!
