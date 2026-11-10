#include <filesystem>
#include <fstream>
#include <string>
#include <variant>
#include <gtest/gtest.h>
#include "ImageLoader.h"
#include "ImageInfo.h"

TEST(ImageLoaderTest, ReturnsErrorWhenFileDoesNotExist) {
    ImageLoader loader;
    std::filesystem::path path = "fake.png";
    auto result = loader.load(path);

    // we should get an error message
    ASSERT_TRUE(std::holds_alternative<std::string>(result));

    // Check if the error message is not empty
    std::string errorMessage = std::get<std::string>(result);
    EXPECT_FALSE(errorMessage.empty());
}

TEST(ImageLoaderTest, ReturnsErrorWhenFilePathIsEmpty) {
    ImageLoader loader;
    std::filesystem::path emptyPath = "";
    auto result = loader.load(emptyPath);

    // we should get an error message
    ASSERT_TRUE(std::holds_alternative<std::string>(result));

    // Check if the error message is not empty
    std::string errorMessage = std::get<std::string>(result);
    EXPECT_FALSE(errorMessage.empty());
}

// Fixture class with a a temporary PNG image
class ImageLoaderTestWithTemporaryPng : public ::testing::Test {
protected:
    // Gets the official operating system directory designated for temporary files
    std::filesystem::path tempPath = std::filesystem::temp_directory_path() / "temp_1x2_test.png";

    // setup for every TEST_F
    void SetUp() override {

        const unsigned char minimal1x2Png[] = {
            // --- PNG Signature (Magic Bytes) ---
            0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
            // --- IHDR Chunk (Image Header) ---
            0x00, 0x00, 0x00, 0x0D,
            0x49, 0x48, 0x44, 0x52,
            0x00, 0x00, 0x00, 0x01,        // Width:  1 pixel
            0x00, 0x00, 0x00, 0x02,        // Height: 2 pixels
            0x08, 0x06, 0x00, 0x00, 0x00,  // 8-bit depth, RGBA color type
            0xF5, 0x4D, 0x36, 0x86,
            // --- IDAT Chunk (Image Data) ---
            0x00, 0x00, 0x00, 0x11,
            0x49, 0x44, 0x41, 0x54,
            0x78, 0x9C, 0x63, 0x60, 0x60, 0xF8, 0x0F, 0x00,
            0x00, 0x11, 0x00, 0x01, 0x9E, 0x24, 0x7E, 0x59,
            0x00,
            // --- IEND Chunk (End of File) ---
            0x00, 0x00, 0x00, 0x00,
            0x49, 0x45, 0x4E, 0x44,
            0xAE, 0x42, 0x60, 0x82
        };

        std::ofstream file(tempPath, std::ios::binary);
        ASSERT_TRUE(file.is_open());
        file.write(reinterpret_cast<const char*>(minimal1x2Png), sizeof(minimal1x2Png));
        file.close();
        ASSERT_TRUE(file.good());
    }

    // clean up after every TEST_F
    void TearDown() override {
        if (std::filesystem::exists(tempPath)) {
            std::filesystem::remove(tempPath);
        }
    }
};

TEST_F(ImageLoaderTestWithTemporaryPng, SuccessfullyLoadsValidImage) {
    ImageLoader loader;

    auto result = loader.load(tempPath);

    // we should get the image infos
    ASSERT_TRUE(std::holds_alternative<ImageInfo>(result));
    
    ImageInfo info = std::get<ImageInfo>(result);
    EXPECT_EQ(info.width, 1);
    EXPECT_EQ(info.height, 2);
    EXPECT_EQ(info.name, tempPath.filename().string());
}
