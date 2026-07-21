#!/bin/bash

echo "export MEMU_HOME=/workspace/YSYX/memu" >> ~/.bashrc
echo "export AM_HOME=/workspace/YSYX/abstract-machine" >> ~/.bashrc
echo "export AM_TEST_HOME=/workspace/YSYX/am-kernels" >> ~/.bashrc
echo "export NVBOARD_HOME=/workspace/YSYX/nvboard" >> ~/.bashrc
echo "export NPC_HOME=/workspace/YSYX/npc" >> ~/.bashrc

git submodule update --init --recursive --depth 1
