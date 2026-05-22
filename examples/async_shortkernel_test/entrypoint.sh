#!/bin/bash
set -e

export GVIRTUS_HOME=/opt/GVirtuS
export EXTRA_NVCCFLAGS='--cudart=shared'
export GVIRTUS_LOGLEVEL=10000
export LD_LIBRARY_PATH=${GVIRTUS_HOME}/lib:${GVIRTUS_HOME}/lib/frontend:${LD_LIBRARY_PATH}

# Recompile GVirtuS to pick up the latest changes
cd ${GVIRTUS_HOME}/build && make -j$(nproc) && make install
if [ $? -ne 0 ]; then
    echo "Error: Failed to compile GVirtuS."
    exit 1
fi

cd "${GVIRTUS_HOME}/examples/async_shortkernel_test"

nvcc async_shortkernel_test.cu -o async_shortkernel_test_app \
    -L${GVIRTUS_HOME}/lib/frontend \
    -L${GVIRTUS_HOME}/lib/ \
    -lcuda -lcudart

./async_shortkernel_test_app
