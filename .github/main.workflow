workflow "Build project" {
  on = "push"
  resolves = ["Run build"]
}

action "Run build" {
  uses = "actions/bin/filter@46ffca7632504e61db2d4cb16be1e80f333cb859"
  runs = "make"
  args = "build"
}
