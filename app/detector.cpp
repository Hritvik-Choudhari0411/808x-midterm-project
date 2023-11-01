/**
 * @file detector.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Detector class source file.
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <detector.hpp>


acme::Detector::Detector(double confidence_threshold_, const std::vector<std::string> &classes_) {
    // Constructor to initialize a Detector object and create the model network
    InitModel(confidence_threshold_, classes_);

    // Warm up the model by running it once before performing actual detection
    WarmUp();
}
acme::Detector::~Detector() {}
    // Destructor
std::vector<acme::Detections> acme::Detector::Detect(const cv::Mat& frame) {
    // Detect objects in the given frame and return a vector of Detections
    std::vector<acme::Detections> detections = {};

    // Create a Mat to store the input blob
    cv::Mat blob;
    if ( !frame.empty() ) {
        // Create a blob from the input frame to feed into the model
        blob = cv::dnn::blobFromImage(frame, scale_factor_, size_factor, mean_factor, swap_factor, crop_factor);

        // Set the input for the model
        model.setInput(blob);
        model_output.clear();

        // Run a forward pass of the model
        model.forward(model_output, layer_outputs);
        cv::Size image_size = frame.size();

        // Process the model's outputs to extract detections
        detections = ProcessModel(image_size);
    }
    return detections;
}

void acme::Detector::SetClasses(const std::vector<std::string> &classes) {
    classes_ = classes;
}

void acme::Detector::FixNmsThresh(const double nms_thresh) {
    nms_threshold_ = nms_thresh;
}

void acme::Detector::FixInputWidth(const int input_width) {
    input_width_ = input_width;
}

void acme::Detector::FixInputHeight(const int input_height) {
    input_height_ = input_height;
}

void acme::Detector::FixScaleFactor(const double scale_factor) {
    scale_factor_ = scale_factor;
}

void acme::Detector::FixSwapRB(const bool swap_rb) {
    swap_factor = swap_rb;
}

void acme::Detector::FixMean(const cv::Scalar &mean) {
    mean_factor = mean;
}

void acme::Detector::CropImage(const bool crop_img) {
    crop_factor = crop_img;
}

void acme::Detector::FixBackend(const int backend) {
    backend_ = backend;
}

void acme::Detector::FixTarget(const int target) {
    target_ = target;
}

void acme::Detector::FixNumChannels(const int num_channels) {
    num_channels_ = num_channels;
}

void acme::Detector::InitModel(double confidence_threshold_, std::vector<std::string> classes_) {
    // Setting default values for model variables
    confidence_threshold_ = confidence_threshold_;

    classes_ = classes_;

    nms_threshold_ = 0.4;

    input_width_ = 416;

    input_height_ = 416;

    size_factor = cv::Size(input_width_, input_height_);

    scale_factor_ = 0.00392157;

    mean_factor = cv::Scalar();

    swap_factor = true;

    crop_factor = false;

    backend_ = 0;

    target_ = 0;

    num_channels_ = 3;

    // Set classes default value for the model
    all_classes_ = {"person" };

    // Set weights file path
    std::string weights_path = "../data/yolov4-tiny.weights";

    // Set config file path
    std::string config_path = "../data/yolov4-tiny.cfg";

    // Create a model
    model = cv::dnn::readNet(weights_path, config_path);

    // Set network backend using the set backend value
    model.setPreferableBackend(backend_);

    // Set network target using the set target value
    model.setPreferableTarget(target_);

    // Get output layer names for the model
    layer_outputs = model.getUnconnectedOutLayersNames();
}

void acme::Detector::WarmUp() {
    // create a temporary Mat object
    cv::Mat temp = cv::Mat::zeros(cv::Size(416, 416), CV_8UC3);

    // run Detector on the temporary Mat as a warmup
    Detect(temp);
}

std::vector<acme::Detections> acme::Detector::ProcessModel(const cv::Size &size) {
     // Create vectors to store class names, confidences, bounding boxes, and indices
    std::vector<acme::Detections> detections;
    std::vector<std::string> class_names;
    std::vector<float> confidences;
    std::vector<cv::Rect> bboxes;
    std::vector<int> indices;

    for ( cv::Mat &output : model_output ) {
        // Cast the Mat data into float data
        auto *data = reinterpret_cast<float*>(output.data);
        for ( int i = 0 ; i < output.rows ; i++, data += output.cols ) {
            // Get the center coordinates of the detected bounding box
            int x_center =  static_cast<int>(data[0]*size.width);
            int y_center = static_cast<int>(data[1]*size.height);

            // Get scores for the output
            cv::Mat scores = output.row(i).colRange(5, output.cols);

            cv::Point class_id_point;

            double confidence;

            // perform minMaxLoc to get global min n max in scores
            cv::minMaxLoc(scores, 0, &confidence, 0, &class_id_point);
            if ( confidence > confidence_threshold_ ) {
                // Detected class id
                int class_id = class_id_point.x;

                // Detected class name
                std::string cl4ss = all_classes_[class_id];

                auto iter = std::find(classes_.begin(), classes_.end(), cl4ss);
                if ( iter != classes_.end() ) {
                    x_center = std::max(0, x_center);
                    y_center =  std::max(0, y_center);

                    // Detected bounding box width
                    int width = static_cast<int>(data[2]*size.width);

                    // Detected bounding box height
                    int height = static_cast<int>(data[3]*size.height);

                    // Calculate top-left coordinates
                    int x_left = x_center - width / 2;
                    int y_top = y_center - height / 2;

                    // Create a cv::Rect object
                    cv::Rect bbox(x_left, y_top, width, height);

                    // Store the class names in a vector
                    class_names.push_back(cl4ss);

                    // Store the confidences in a vector
                    confidences.push_back(static_cast<float>(confidence));

                    // Store the bounding box in a vector
                    bboxes.push_back(bbox);
                }
            }
        }
    }

    // Applying Non Maximum Suppression
    cv::dnn::NMSBoxes(bboxes, confidences, confidence_threshold_, nms_threshold_, indices);

    for ( int index : indices ) {
        cv::Rect bounding_box = bboxes[index];
        double conf = static_cast<double>(confidences[index]);
        std::string name = class_names[index];

        // Creating Detections object
        Detections box(bounding_box, conf, name);

        // Store the Detections objects in a vector
        detections.push_back(box);
    }
    return detections;
}