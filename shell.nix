{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [ cmake ];
  buildInputs = with pkgs; [ glfw imgui ];
}
