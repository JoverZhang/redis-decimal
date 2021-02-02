FROM redisfab/rmbuilder:6.0.9-x64-bionic as builder

# Build the source
ADD . /builder
WORKDIR /builder
RUN set -ex; \
    cmake .; \
    make clean; \
    make; \
    ./.tests/tests


# Package the runner
FROM redisfab/redis:6.0-latest-x64-bionic
ENV LIBDIR /usr/lib/redis/modules

WORKDIR /data
RUN set -ex;\
    mkdir -p "$LIBDIR";
COPY --from=builder /builder/lib/libdecimal.so "$LIBDIR"

CMD ["redis-server", "--loadmodule", "/usr/lib/redis/modules/libdecimal.so"]
