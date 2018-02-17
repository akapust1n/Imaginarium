#!/bin/bash

eval "$(ssh-agent -s)" # Start ssh-agent cache
chmod 600 .travis/travis # Allow read access to the private key
ssh-add .travis/travis # Add the private key to SSH

git config --global push.default matching
git remote add deploy ssh://git@$IP:$PORT$WDEPLOY_DIR
git push deploy backend

# Skip this command if you don't need to execute any additional commands after deploying.
ssh -o "StrictHostKeyChecking no" apps@$IP -p $PORT <<EOF
  pwd
  cd $WDEPLOY_DIR
  pwd
  cd backend
  qmake
  make
  ./main
EOF
