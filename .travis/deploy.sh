#!/bin/bash

eval "$(ssh-agent -s)" # Start ssh-agent cache
chmod 600 .travis/travis # Allow read access to the private key
ssh-add .travis/travis # Add the private key to SSH

# Skip this command if you don't need to execute any additional commands after deploying.
ssh apps@$IP -p $PORT << EOF
  cd $DEPLOY_DIR
  git reset --hard origin/frontend
  git pull  origin frontend
  pkill -f serve
  npm install
  npm run build
  nohup serve -s build -p 3000 > /dev/null 2> /dev/null < /dev/null &
EOF
