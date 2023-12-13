# TSCL Core Libraries - **C**

The TSCL Core is a robust and versatile set of libraries designed to serve as the foundational framework for essential programming tasks, ensuring seamless development across a variety of applications. At its core, TSCL (Thread, Stream, Lambda, and Input Reader) provides a comprehensive suite of tools that empower developers to create efficient and responsive software solutions.

1. **Thread Management:**
   TSCL Core simplifies concurrent programming by offering a powerful thread management library. Developers can effortlessly implement multithreading capabilities, enhancing the performance and responsiveness of their applications. This feature is particularly valuable for handling parallel tasks and optimizing resource utilization.

2. **File Stream Operations:**
   With a focus on efficient file handling, TSCL Core includes a robust file stream library. Developers can easily read from and write to files, ensuring seamless data manipulation and storage. This capability is crucial for applications that involve data persistence, logging, or any file-based operations.

3. **Lambda Functions Support:**
   TSCL Core embraces the flexibility and expressiveness of lambda functions, providing developers with a streamlined way to define and use anonymous functions within their code. Lambda functions empower developers to write concise and expressive code, enhancing code readability and maintainability.

4. **Input Readers:**
   The TSCL Core includes versatile input readers that simplify the process of user input handling. Whether dealing with command-line inputs, user interfaces, or other input sources, these readers facilitate a consistent and user-friendly experience. This feature is especially beneficial for applications that rely on interactive user input.

By combining these essential components, the TSCL Core ensures a solid foundation for software development, promoting code efficiency, maintainability, and scalability. Whether you're building a multi-threaded application, managing file operations, leveraging lambda functions, or handling user inputs, TSCL Core provides a comprehensive toolkit to streamline your development process and elevate the performance of your software projects.

## Who is This For?

This guide is designed for developers of all skill levels who want to use the Meson build system for their projects. It assumes basic familiarity with command-line interfaces and project organization.

## Prerequisites

Before getting started, make sure you have the following installed:

- **Meson Build System**: This project relies on Meson. If you don't have Meson installed, visit the official [Meson website](https://mesonbuild.com/Getting-meson.html) for installation instructions.

## Setting up Meson Build

1. **Install Meson**:
   - Follow the installation instructions on the [Meson website](https://mesonbuild.com/Getting-meson.html) for your operating system.

## Setting up, Compiling, Installing, and Running the Project

1. **Create a Wrap File**:

Create a directory named subprojects in the root directory, next create a file named `tscl-x<name>-c.wrap` in the `subprojects` directory of your project with the following content:

   ```bash
   # ================ #
   #  TSCL Wrap File. #
   # ================ #
   [wrap-git]
   url = https://github.com/trilobite-stdlib/tscl-<name>-c.git
   revision = main
   
   [provide]
   tscl-x<name>-c = tscl_x<name>_c_dep
   ```

2. **Integrate Wrap File in Meson Build**:
   ```meson
   project('my_project', 'c',
       version : '0.1',
       default_options : ['warning_level=3'])

   exe = executable('my_project', 'my_project.c',
       dependencies : dependency('tscl-x<name>-c'), # add this line
       install : true)

   test('basic', exe)
   ```

3. **Compile the Project**:
   ```bash
   meson setup builddir
   meson compile -C builddir
   ```

4. **Visit the reference guide to learn how to this**

Here is the link to the [Refrence Docs](https://trilobite.home.blog/reference-docs/)

## Including the Demo and Running Tests

To include the demo and run tests, you can use the following options when configuring the build:

- **Including the Demo**: Add `-Dwith_demo=enabled` when configuring the build.
- **Running Tests**: Add `-Dwith_test=enabled` when configuring the build.

Example:

```bash
meson setup builddir -Dwith_demo=enabled -Dwith_test=enabled
```

## Contributing

If you're interested in contributing to this project, please consider opening pull requests or creating issues on the [GitHub repository](https://github.com/dreamer-coding-555/meson-lib-c). Be sure to read the documentation on the [project website](https://trilobite.home.blog).

## Feedback and Support

If you encounter any issues, have questions, or would like to provide feedback, don't hesitate to open an issue on the [GitHub repository](https://github.com/dreamer-coding-555/meson-lib-c/issues).

## License

This project is licensed under the [Apache License 2.0](LICENSE).

---

Thank you for choosing this project with the Meson build system. Happy coding and building amazing projects!

## Contact

If you have questions or want to get in touch regarding programming solutions, you can find a way to contact me on my [website](https://trilobite.code.blog/contact/).
