FROM ghcr.io/wiiu-env/devkitppc:20240704

COPY --from=wiiuenv/libgui:20220109 /artifacts /opt/devkitpro

WORKDIR project
