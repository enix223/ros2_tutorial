# ros2 + cpp tutorial

## FAQ

* If you are using pyenv in your shell, please make sure `pyenv` is removed from your path when first run `colcon build`

    ```shell
    export PATH=$(echo $PATH | tr ':' '\n' | grep -v "pyenv" | tr '\n' ':' | sed 's/:$//')
    ```
