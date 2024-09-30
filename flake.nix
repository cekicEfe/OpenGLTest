{
  description = "OpenGL development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: 
    flake-utils.lib.eachDefaultSystem (system: let 
      pkgs = import nixpkgs {
        inherit system;
      };
    in {
      devShell = pkgs.mkShell {
        # Dependencies for OpenGL
        buildInputs = [
          pkgs.gcc                   # C++ compiler
          pkgs.cmake                 # For building
          pkgs.glm
	  pkgs.freetype
	  pkgs.libpng
	  pkgs.assimp
	  pkgs.gdb                   # Debugger
          pkgs.glfw-wayland          # GLFW for window and context management
          pkgs.imgui                 # ImGui for UI development
          pkgs.pkg-config            # To manage compilation flags
	  pkgs.libxkbcommon
	  pkgs.libGL
	];

        # Useful environment variables
      shellHook = ''
	export LD_LIBRARY_PATH=${pkgs.glfw}/lib:${pkgs.assimp}/lib:${pkgs.freetype}/lib:${pkgs.libpng}/lib:${pkgs.wayland}/lib:${pkgs.libxkbcommon}/lib:${pkgs.libGL}/lib:$LD_LIBRARY_PATH
	echo "OpenGL development environment is ready!"
        '';
      };
    });
}
