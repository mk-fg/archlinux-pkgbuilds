# Based on rtl8812au-rpi-dkms-git by sekret from AUR

_p=rtl8812au
pkgname=rtl8812au-5.1.5-rpi-git
pkgver=5.1.5
pkgrel=1
pkgdesc="Realtek 8812au USB WiFi module"
arch=(armv7h)
url="https://github.com/mk-fg/rtl8812au"
license=(proprietary)
depends=(dkms linux-raspberrypi linux-raspberrypi-headers)
makedepends=(git)
install=$pkgname.install
source=("$_p::git+$url" dkms.conf)
sha256sums=(SKIP SKIP)

pkgver() {
	cd $_p
	rel=$( gawk \
		'/^#define\s+DRIVERVERSION\s+/ && match($3,/"v([0-9]\S*)"/,m) {print m[1]}' \
		include/rtw_version.h )
	[[ -n "$rel" ]] || exit 1
	printf "%s.%s.%s" "$rel" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

prepare() {
	cd $_p
	patch -li Makefile.enable-rpi.patch
}

package() {
	cd $_p
	mkdir -p "$pkgdir/usr/src/$_p-$pkgver"
	cp -a * "$pkgdir/usr/src/$_p-$pkgver"
	install -Dm644 "$srcdir/dkms.conf" "$pkgdir/usr/src/$_p-$pkgver"
	sed -e "s/@PKGBASE@/$_p-dkms/" -e "s/@PKGVER@/$pkgver/" -i "$pkgdir/usr/src/$_p-$pkgver/dkms.conf"
}
