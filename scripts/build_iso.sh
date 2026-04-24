#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_DIR="$ROOT_DIR/out"
ISO_ROOT="$ROOT_DIR/iso_root"

mkdir -p "$ISO_ROOT/EFI/BOOT"

cp "$OUT_DIR/bootx64.efi" "$ISO_ROOT/EFI/BOOT/BOOTX64.EFI"
cp "$OUT_DIR/kernel.elf" "$ISO_ROOT/kernel.elf"

if command -v xorriso >/dev/null 2>&1; then
  xorriso -as mkisofs -R -f -e EFI/BOOT/BOOTX64.EFI -no-emul-boot \
    -o "$ISO_ROOT/ILBARSDOWS.iso" "$ISO_ROOT"
  echo "ISO produced: $ISO_ROOT/ILBARSDOWS.iso"
else
  echo "xorriso bulunamadı; ISO oluşturma atlandı." >&2
  exit 1
fi
