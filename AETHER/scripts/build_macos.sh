#!/usr/bin/env bash
set -euo pipefail
EDITION="${1:-PRO}"
cmake -B build -S . -DAETHER_EDITION="$EDITION"
cmake --build build --config Release
