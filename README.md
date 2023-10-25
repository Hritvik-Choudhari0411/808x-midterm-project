# 808x-midterm-project

![CICD Workflow status](https://github.com/KshitijKarnawat/808x-midterm-project/actions/workflows/main.yml/badge.svg)
[![codecov](https://codecov.io/gh/KshitijKarnawat/808x-midterm-project/branch/devel/graph/badge.svg)](https://codecov.io/gh/KshitijKarnawat/808x-midterm-project)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Project Overview

In the context of the Collaborative Industrial Robot (CIR), our project focuses on the imperative task of real-
time human detection and tracking. Our solution entails a specialized human detection and tracking module,
leveraging advanced computer vision algorithms. It abstracts the intricacies of the underlying algorithms
and offers three operational modes: training, testing, and real-time execution.
Throughout the project, we will follow Agile Iterative Processs (AIP) to optimize our software devel-
opment process. In the initial sprint, we implement backlog requirements, monitor bugs, and introduce
features, while daily meetings ensure progress and resolve conflicts. Each sprint concludes with an iteration
review for code and backlog assessment in preparation for the next sprint. This can be integrated with other
modules like Controls and Motion planning/navigation to develop a fully operational robot.

## Author information

- Kshitij Karnawat (<kshitij@terpmail.edu>)
- Hritvik Choudhari (<hac@terpmail.edu>)

## License

License under MIT License.

## Dependencies

- OpenCV 4.7.* or higher
- CMake 3.2 or higher
- Ubuntu 18.04 or higher
- GoogleTest (for testing)
- Doxygen
- Graphviz
- Cpplint
- CppCheck

## Installation

### [Intalling OpenCV](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)

```sh
sudo apt-get install libopencv-dev
```

## UML Diagrams

![UML Diagram](UML_Diagrams/Revised/UML_Class_Diagram.png)

## Quad Chart

![Quad Chart](./etc/quad_chart.png)

## [Agile Iterative Process Sheet](https://docs.google.com/spreadsheets/d/1ClVrcb1FtqD7OdxFqPrhnZTfMS6CZsh9HTW7clclphI/edit?usp=sharing)

## [Planning Sheet](https://docs.google.com/document/d/1iMmyf-nXXenmKZDXkSh4wu5QEsInimkXTg0Oqb2PvHU/edit?usp=sharing)

## API and other developer documentation

### Run

```sh
# Running the application
./build/app/shell-app

# Building doxygen documentation
cmake --build build/ --target docs
```

### Test

```sh
# Running test
cd build/; ctest; cd -

# Running Code Coverage
cmake -D WANT_COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug -S ./ -B build/
cmake --build build/ --clean-first --target all test_coverage
```

### Demo

## Known Issues

## [Other development Documets](https://opencv.org/)

## [Proposal Video](https://youtu.be/rU7ts5qoDmg)
