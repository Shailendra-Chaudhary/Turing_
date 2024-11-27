#include <string>
#include <cstdint>
#include <iostream>
#include <tensorflow/lite/c/c_api.h>

// Load the TensorFlow Lite model from a file
TfLiteStatus LoadModel(const std::string& model_path, TfLiteInterpreter** interpreter) {
    TfLiteModel* model = TfLiteModelCreateFromFile(model_path.c_str(), &error_reporter);
    if (model == nullptr) {
        TF_LITE_REPORT_ERROR(error_reporter, "Failed to initialize model from file");
        return kTfLiteError;
    }
    
    TfLiteInterpreterOptions* options = TfLiteInterpreterOptionsCreate();
    TfLiteStatus status = TfLiteInterpreterCreateFromModelAndOptions(model, options, interpreter);
    TfLiteModelDelete(model);
    TfLiteInterpreterOptionsDelete(options);
    
    if (status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "Failed to create interpreter");
        return kTfLiteError;
    }
    
    return kTfLiteOk;
}

// Allocate tensors
TfLiteStatus AllocateTensors(TfLiteInterpreter* interpreter) {
    return TfLiteInterpreterAllocateTensors(interpreter);
}

// Run the interpreter to perform predictions
TfLiteStatus Invoke(TfLiteInterpreter* interpreter) {
    return TfLiteInterpreterInvoke(interpreter);
}

// Get output tensor data
TfLiteStatus GetOutputTensor(TfLiteInterpreter* interpreter, int output_index, float** output_data) {
    TfLiteTensor* tensor = TfLiteInterpreterOutputTensor(interpreter, output_index);
    return TfLiteTensorDataCopy(tensor, output_data);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <model_path>" << std::endl;
        return 1;
    }

    std::string model_path(argv[1]);
    TfLiteInterpreter* interpreter;
    TfLiteStatus status = LoadModel(model_path, &interpreter);
    if (status != kTfLiteOk) {
        return 1;
    }

    status = AllocateTensors(interpreter);
    if (status != kTfLiteOk) {
        return 1;
    }

    // Input tensor index
    int input_index = TfLiteInterpreterInputTensorIndex(interpreter, 0);
    TfLiteTensor* input_tensor = TfLiteInterpreterTensor(interpreter, input_index);

    // Sample sensor data
    float sensor_data[input_tensor->bytes / sizeof(float)] = {
        10.0f,  // Example sensor data
        20.0f,  // Example sensor data
        30.0f   // Example sensor data
    };

    // Set input data
    status = TfLiteTensorCopyFromBuffer(input_tensor, sensor_data, input_tensor->bytes);
    if (status != kTfLiteOk) {
        return 1;
    }

    // Invoke the model
    status = Invoke(interpreter);
    if (status != kTfLiteOk) {
        return 1;
    }

    // Get output tensor index and data
    int output_index = TfLiteInterpreterOutputTensorIndex(interpreter, 0);
    float* output_data;
    status = GetOutputTensor(interpreter, output_index, &output_data);
    if (status != kTfLiteOk) {
        return 1;
    }

    // Output result
    std::cout << "Prediction: " << output_data[0] << std::endl;

    return 0;
}
