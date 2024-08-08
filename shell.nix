{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  packages = with pkgs; [
    git
    pkgconf
    clang
    python3
    lld
    gnumake
    cmake
    ccls
  ];

  nativeBuildInputs = with pkgs; [
    pkg-config
    autoPatchelfHook
    installShellFiles
    clang
    cmake
    ccls
  ];

  runtimeDependencies = with pkgs; [
    vulkan-loader
    libGL
    libGLU
    libglvnd
    xorg.libX11
    xorg.libXcursor
    xorg.libXinerama
    xorg.libXext
    xorg.libXrandr
    xorg.libXrender
    xorg.libXi
    xorg.libXfixes
    libxkbcommon
    alsa-lib
    libpulseaudio
    mesa
    dbus
    dbus.lib
    fontconfig
    fontconfig.lib
    udev
  ];

  buildInputs = with pkgs; [
    scons
    clang
    lld
    pkgconf
    cmake
    ccls
  ];
}
