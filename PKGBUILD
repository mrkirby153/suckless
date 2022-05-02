# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# The following guidelines are specific to BZR, GIT, HG and SVN packages.
# Other VCS sources are not natively supported by makepkg yet.

# Maintainer: Your Name <youremail@domain.com>
pkgbase=mrkirby153-suckless
pkgname=(mrkirby153-st-git mrkirby153-dwm-git mrkirby153-dmenu-git)
_pkgs=('st' 'dwm' 'dmenu')
pkgver=r41.7824597
pkgrel=1
arch=('any')
license=('MIT')
makedepends=('git' 'make' 'fontconfig' 'freetype2' 'xorgproto' 'libxft-bgra' 'libxinerama') # 'bzr', 'git', 'mercurial' or 'subversion'
source=('suckless::git+https://github.com/mrkirby153/suckless.git')
noextract=()
md5sums=('SKIP')

pkgver() {
	cd "$srcdir/suckless"
	printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

prepare() {
	cd "$srcdir/suckless"
	git submodule update --init --force

	for _pkg in ${_pkgs[*]}; do
		cd "$srcdir/suckless/$_pkg"
		./setup.sh
	done
}

build() {
	for _pkg in ${_pkgs[*]}; do
		cd "$srcdir/suckless/$_pkg/source"
		make
	done
}

_install() {
	cd "$srcdir/suckless/$1/source"
	make DESTDIR="$pkgdir" install
}

package_mrkirby153-st-git() {
	_install "st"
}

package_mrkirby153-dwm-git() {
	_install "dwm"
}

package_mrkirby153-dmenu-git() {
	_install "dmenu"
}
