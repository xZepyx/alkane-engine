# Getting Started
If you're reading these docs, I guess I don't need to explain what's alkane etc. As may have came here
after knowing what's alkane and you want to use it.

## Installation
As there isn't a way to install the framework right now. Prefer copying the libs directly to /usr/include

> [!NOTE]
> You should have KHR/khrplatform.h, glad/glad.h, GLFW/glfw3.h and stb_image.h installed. 

```
git clone https://github.com/alkane-framework/alkane-engine.git
cd alkane-engine
sudo cp -r src/alkane /usr/include
```

## Setting up the project
Now after installing the framework you should be able to import headers like: `#include <alkane/someheader.hpp>`

* Steps:
  - I don't need to explain this. Just setup your project as you usually do
  - Make a CMakeLists or whatever way you use to compile ur projects.
  - Test: Try import headers to confirm installation

## Continue
Go to the [Next Page](./CreatingAWindow.md) 
