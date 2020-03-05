# How to Git

1. The [Git website](https://git-scm.com/about) provides extensive documentation on Git and it is highly recommended that you check it out first.
1. Common Git Command
      1. Help
            1. `git -h` and `git --help`
            1. `git COMMAND -h`
      1. Save progress
            1. `git add DIR` add the files or directory `DIR`
            1. `git commit -m "Commit message"` commit current progress with the message
      1. Branching
            1. `git branch NEW_BRANCH` creates a new branch with named `NEW_BRANCH`
            1. `git checkout BRANCH` switches to an existed branch named `BRANCH`
            1. `git checkout -b NEW_BRANCH` creates and switches to the new branch named `NEW_BRANCH`
            1. `git merge BRANCH` merges the current branch with the other branch named `BRANCH`
      1. Remote Repo interaction
            1. `git remote add REPO_NAME REPO_URL` adds the repository at `REPO_URL` with name `REPO_NAME`
            1. `git push REPO_NAME` pushes the locally committed code to the remote repository with name `REPO_NAME`
            1. `git pull REPO_NAME` fetches the remote repository and merges it with the current branch
