#!/bin/bash

eval "$(ssh-agent -s)" # Start ssh-agent cache
chmod 600 .travis/travis # Allow read access to the private key
ssh-add .travis/travis # Add the private key to SSH

# Skip this command if you don't need to execute any additional commands after deploying.
ssh apps@$IP -p $PORT << EOF
  cd $DEPLOY_DIR
  git reset --hard origin/frontend~1
  git pull  origin frontend
  pkill -f serve
  npm install
  npm run build
  nohup serve -s -p 3000 -c 0 build > /dev/null 2> /dev/null < /dev/null &

EOF
travis_terminate 0
