void MainWindow::createFolder(const std::string& folderName) {
    Folder newFolder;
    newFolder.name = folderName;
    newFolder.color = getRandomColor(); // Function to get a random color
    folders.push_back(newFolder); // Add the new folder to the list of folders
}

void MainWindow::deleteFolder(const std::string& folderName) {
    auto it = std::find_if(folders.begin(), folders.end(), & {
        return folder.name == folderName;
    });
    if (it != folders.end() && it->items.empty()) {
        folders.erase(it); // Remove the folder if it is empty
    }
}
