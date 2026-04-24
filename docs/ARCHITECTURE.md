# ILBARSDOWS Mimari Özeti

## Boot Akışı
1. `BOOTX64.EFI` UEFI ortamında çalışır.
2. GOP ayarlanır ve bellek haritası okunur.
3. Kernel ELF RAM'e yüklenir.
4. `BootInfo` yapısı ile çekirdeğe kontrol devredilir.

## Çekirdek Katmanları
- **HAL/Arch**: giriş noktası, düşük seviye init
- **MM**: paging, fiziksel çerçeve allocator, heap
- **INT**: IDT/ISR/IRQ yönlendirme
- **SCHED**: round-robin task yürütme
- **SYSCALL**: kullanıcı-çekirdek geçiş tablosu

## UI Alt Sistemi
- Framebuffer compositor
- Rounded-window rasterizer
- Görev çubuğu ve başlat menüsü katmanı
- Animasyon zaman çizelgesi

## Uygulama Katmanı
Uygulamalar çekirdeğe doğrudan bağlı statik modüllerdir. Gelecekte ayrı kullanıcı alanına taşınacaktır.
