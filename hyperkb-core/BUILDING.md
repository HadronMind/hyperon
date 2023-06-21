# How to build

[Conan](https://docs.conan.io/2/index.html) is used to manager HyperKB's
dependencies. You can refer to   `conanfile.py` to get details on the building
requirements.

To build HyperKB, you should have conan installed correctly on your
computer. Then follow steps below to compile the project:

1. Install dependencies to conan cache. This requires a rerun in case you update
   `conanfile.py`.

```
conan install . --build=missing
```

2. Build the source

```
conan build .
```