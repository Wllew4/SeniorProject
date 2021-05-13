@echo off
git checkout main
git merge working
git push --force origin main
git checkout working
pause