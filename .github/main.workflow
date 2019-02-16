workflow "Build Repository" {
  on = "push"
  resolves = ["Run build"]
}

action "Run build" {
  uses = "actions/action-builder/shell@master"
  runs = "make"
  args = "build"
}
