# lggm
How to start:
```
script_file="${PWD}/do_tune_submodules"

cat << EOF_SCRIPT_FILE > "${script_file}"
git fetch --all --recurse-submodules \
    && git config user.name "lktrgl" \
    && git config user.email "32882989+lktrgl@users.noreply.github.com" \
    && git stash clear \
    && git stash \
    && git checkout master \
    && git rebase origin/master \
    && git stash pop || true
EOF_SCRIPT_FILE

chmod a+x "${script_file}"

git clone --recurse-submodules --verbose --remote --progress https://github.com/lktrgl/lggm.git \
    && cd lggm \
    && git submodule foreach --recursive git status \
    && git submodule foreach --recursive "${script_file}" \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make all

git config user.email "32882989+lktrgl@users.noreply.github.com"

rm -vf "${script_file}"

unset script_file
```
