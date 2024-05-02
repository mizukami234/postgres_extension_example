FROM postgres:14

RUN apt-get update && apt-get install -y \
    git \
    make \
    gcc \
    clang-11 \
    postgresql-server-dev-14

COPY ./extension /extension
WORKDIR /extension

RUN make USE_PGXS=1 PG_CONFIG=/usr/bin/pg_config
RUN make USE_PGXS=1 PG_CONFIG=/usr/bin/pg_config install
