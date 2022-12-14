{
  description = "Compilers project";

  inputs = {
    # Pointing to the current stable release of nixpkgs. You can
    # customize this to point to an older version or unstable if you
    # like everything shining.
    #
    # E.g.
    #
    nixpkgs.url = "nixpkgs/nixos-unstable";
    # nixpkgs.url = "github:NixOS/nixpkgs/21.05";

    utils.url = "github:numtide/flake-utils";
    utils.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    # Add the system/architecture you would like to support here. Note that not
    # all packages in the official nixpkgs support all platforms.
    "x86_64-linux" # "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: let pkgs = import nixpkgs {
                   inherit system;

                   # Add overlays here if you need to override the nixpkgs
                   # official packages.
                   overlays = [];
                     
                   # Uncomment this if you need unfree software (e.g. cuda) for
                   # your project.
                   #
                   # config.allowUnfree = true;
                 };
             in {
               devShell = pkgs.mkShell rec {
                 # Update the name to something that suits your project.
                 name = "compilers-project";
                 
                 packages = with pkgs; [
                   # Development Tools
                   ninja
                   cmake
                   cmakeCurses
                   bison
                   flex
                   
                   # Libraries
                   boost
                   tbb
                   fmt_8
                   spdlog
                   abseil-cpp

                   # Development time dependencies
                   gtest
                 ];

                 # Setting up the environment variables you need during
                 # development.
                 shellHook = let
                   icon = "f121";
                 in ''
                    export CXX="c++"
                    export PS1="$(echo -e '\u${icon}') {\[$(tput sgr0)\]\[\033[38;5;228m\]\w\[$(tput sgr0)\]\[\033[38;5;15m\]} (${name}) \\$ \[$(tput sgr0)\]"
                 '';
               };

               defaultPackage = pkgs.callPackage ./default.nix {};
             });
}
