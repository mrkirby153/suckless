{
  description = "mrkirby153's suckless builds";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    dwm-src = {
      url = "git+https://git.suckless.org/dwm?rev=84d7322113c2bf023f5eaa8537fb0e72d4105046";
      flake = false;
    };
    st-src = {
      url = "git+https://git.suckless.org/st?rev=a0274bc20e11d8672bb2953fdd1d3010c0e708c5";
      flake = false;
    };
    dmenu-src = {
      url = "git+https://git.suckless.org/dmenu?rev=86f0b5119eaa39943013d009967432ffd9d18365";
      flake = false;
    };
  };

  outputs = {
    self,
    nixpkgs,
    ...
  } @ inputs: let
    inherit (nixpkgs) lib;
    systems = ["x86_64-linux" "aarch64-linux"];
    forAllSystems = f: lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});

    mkSuckless = pkgs: {
      name,
      extraDeps ? [],
      preBuild ? "",
    }: let
      dir = ./. + "/${name}";
      patchDir = dir + "/patches";
    in
      pkgs.stdenv.mkDerivation {
        pname = name;
        version = self.shortRev or self.dirtyShortRev or "dirty";
        src = inputs."${name}-src";
        patches = map (p: patchDir + "/${p}") (lib.sort lib.lessThan (lib.attrNames (builtins.readDir patchDir)));
        nativeBuildInputs = [pkgs.pkg-config];
        buildInputs = with pkgs; [libx11 libxft] ++ extraDeps;
        postPatch = lib.optionalString (builtins.pathExists (dir + "/config.h")) ''
          cp ${dir + "/config.h"} config.h
        '';
        inherit preBuild;
        makeFlags = ["DESTDIR=$(out)" "PREFIX="];
        meta = {
          license = lib.licenses.mit;
          platforms = lib.platforms.linux;
          mainProgram = name;
        };
      };

    mkPackages = pkgs: let
      build = mkSuckless pkgs;
    in {
      dwm = build {
        name = "dwm";
        extraDeps = [pkgs.libxinerama];
      };
      st = build {
        name = "st";
        extraDeps = with pkgs; [ncurses];
        preBuild = ''
          export TERMINFO=$out/share/terminfo
          mkdir -p $TERMINFO
        '';
      };
      dmenu = build {
        name = "dmenu";
        extraDeps = [pkgs.libxinerama];
      };
    };
  in {
    packages = forAllSystems (pkgs: let
      p = mkPackages pkgs;
    in
      p
      // {
        default = pkgs.symlinkJoin {
          name = "suckless";
          paths = lib.attrValues p;
        };
      });

    overlays.default = final: prev: {
      aus-suckless = mkPackages final;
    };

    formatter = forAllSystems (pkgs: pkgs.alejandra);
  };
}
