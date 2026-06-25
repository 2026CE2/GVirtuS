#! /bin/bash
ulimit -n 65536
export GVIRTUS_LOGLEVEL=60000
cd ${GVIRTUS_HOME}/build && make -j$(nproc) && make install
${GVIRTUS_HOME}/bin/gvirtus-backend ${GVIRTUS_HOME}/etc/properties.json
#tail -f /dev/null # for debugging