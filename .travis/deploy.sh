#!/bin/bash

eval "$(ssh-agent -s)" # Start ssh-agent cache
chmod 600 .travis/travis # Allow read access to the private key
ssh-add .travis/travis # Add the private key to SSH

git config --global push.default matching
git remote add deploy ssh://git@$IP:$PORT$DEPLOY_DIR
git push deploy frontend

# Skip this command if you don't need to execute any additional commands after deploying.
ssh-copy-id apps@$IP
ssh -o "StrictHostKeyChecking no" apps@$IP -p $PORT <<EOF
  cd $DEPLOY_DIR
  npm install
  npm start
EOF
