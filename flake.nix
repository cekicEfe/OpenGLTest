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
            pkgs.glm
            pkgs.freetype
            pkgs.libpng
            pkgs.assimp
            pkgs.glfw # GLFW for window and context management
            pkgs.imgui # ImGui for UI development
            pkgs.pkg-config # To manage compilation flags
            pkgs.libxkbcommon
            pkgs.libGL
            pkgs.xorg.libX11
            pkgs.mesa
            pkgs.glsl_analyzer
          ];
          #links libraries to shell
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            pkgs.glfw
            pkgs.glsl_analyzer
            pkgs.xorg.libX11
            pkgs.glm
            pkgs.assimp
            pkgs.freetype
            pkgs.libpng
            pkgs.wayland
            pkgs.libxkbcommon
            pkgs.libGL
            pkgs.imgui
            pkgs.mesa
          ];
          shellHook = ''
            	echo "OpenGL development environment is ready!"
                    PS1="[\\u@\\h && OPENGL-DEV-ENV:\\w]\$ "
            	'';
        };
      });
}
