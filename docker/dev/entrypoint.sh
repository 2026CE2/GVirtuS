#! /bin/bash
export GVIRTUS_LOGLEVEL=60000

mkdir gvirtus/build && cd gvirtus/build && cmake .. && make -j$(nproc) && make install
 ${GVIRTUS_HOME}/bin/gvirtus-backend ${GVIRTUS_HOME}/etc/properties.json
#tail -f /dev/null # for debugging