{ pkgs ? import <nixpkgs> { config.allowUnfree = true; } }:
pkgs.mkShell {
  buildInputs = [
    pkgs.curl.dev
    pkgs.cjson
    pkgs.gcc
    pkgs.pkg-config
    pkgs.graphviz
    pkgs.lmstudio
  ];
}
