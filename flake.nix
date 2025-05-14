{
  description = "OpenGL development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
      in {
        devShell = pkgs.mkShell {
          # Dependencies for OpenGL
          buildInputs = [
            pkgs.valgrind
            pkgs.glsl_analyzer
            pkgs.cmake
            pkgs.gcc
            pkgs.gdb

            pkgs.libpng
            pkgs.pkg-config # To manage compilation flags
            pkgs.libxkbcommon
            pkgs.libGL
            pkgs.xorg.libX11
            pkgs.mesa

            pkgs.cglm

            pkgs.freetype
            pkgs.nlohmann_json
            pkgs.lua
            pkgs.sol2
            pkgs.bullet
            pkgs.glm
            pkgs.assimp
            pkgs.glfw # GLFW for window and context management
            pkgs.imgui # ImGui for UI development
          ];
          #links libraries to shell
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            pkgs.glsl_analyzer
            pkgs.xorg.libX11
            pkgs.freetype
            pkgs.libpng
            pkgs.wayland
            pkgs.libxkbcommon
            pkgs.libGL
            pkgs.mesa

            pkgs.cglm

            pkgs.lua
            pkgs.sol2
            pkgs.bullet
            pkgs.glm
            pkgs.assimp
            pkgs.glfw
            pkgs.imgui
          ];
          shellHook = ''
            	echo "OpenGL development environment is ready!"
                    PS1="[\\u@\\h && OPENGL-DEV-ENV:\\w]\$ "
            	'';
        };
      });
}
