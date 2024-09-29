with import <nixpkgs> {};
mkShell {
  packages = [
    assimp
    glxinfo
    glfw-wayland
    glfw
    imgui
    libpng
    freetype
  ];
  buildInputs = [
    glfw-wayland
    glfw
    assimp
    imgui
    libpng
    freetype
  ];
}
