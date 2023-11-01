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

- Kshitij Karnawat (<kshitij@terpmail.umd.edu>)
- Hritvik Choudhari (<hac@terpmail.umd.edu>)

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

## Dependencies Installation

```sh
sudo chmod +x requirements.sh
./requirements.sh
```

## UML Diagrams

![UML Diagram](UML_Diagrams/Revised/UML_Class_Diagram.png)

## Quad Chart

![Quad Chart](./etc/quad_chart.png)

## [Agile Iterative Process Sheet](https://docs.google.com/spreadsheets/d/1ClVrcb1FtqD7OdxFqPrhnZTfMS6CZsh9HTW7clclphI/edit?usp=sharing)

## [Planning Sheet](https://docs.google.com/document/d/1iMmyf-nXXenmKZDXkSh4wu5QEsInimkXTg0Oqb2PvHU/edit?usp=sharing)

## Building and Running

### Build

```sh
# Clone the repository
git clone

# Create a build directory
mkdir build && cd build
cmake ..
make

# To generate documentation
cd ..
cmake --build build/ --target docs
```

### Run

```sh
# Running the application
cd build/
./app/shell-app

# Press 'esc' to exit the application

```

### Test

```sh
# Running test
cd build/; ctest; cd -

# Running Code Coverage
cmake -D WANT_COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug -S ./ -B build/
cmake --build build/ --clean-first --target all test_coverage
```

## Known Issues

- Gtk-Message: 05:12:10.167: Failed to load module "canberra-gtk-module"
- For CodeCov to get 100% coverage, we need to atleast one successful detection getting this on the CodeCov badge is not possible.

## Other development Documets

- [OpenCV Documentation](https://opencv.org/)

## Videos

- [Proposal](https://www.youtube.com/watch?v=stZ0M5cbaZc)
- [Phase 1 Update](https://youtu.be/rU7ts5qoDmg)
- [Phase 2 Update](https://drive.google.com/drive/folders/117Q6IaYHH1USH-lrPJKtHf2k1KUElCaI?usp=sharing)