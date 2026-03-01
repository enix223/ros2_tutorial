# ros2 + cpp tutorial

# 1. Pubsub

* run publisher

    ```sh
    make runsimplepub
    ```

* run subscriber

    ```sh
    make runsimplesub
    ```

# 2. Service call

* run server

    ```sh
    make runservicecallsrv
    ```

* run client

    ```sh
    make runservicecallcli
    ```

## FAQ

* Create a new package

    ```shell
    ros2 pkg create --build-type ament_cmake --license Apache-2.0 cpp_pubsub
    ```

* If you are using pyenv in your shell, please make sure `pyenv` is removed from your path when first run `colcon build`

    ```shell
    export PATH=$(echo $PATH | tr ':' '\n' | grep -v "pyenv" | tr '\n' ':' | sed 's/:$//')
    ```
