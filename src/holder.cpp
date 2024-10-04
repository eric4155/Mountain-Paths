while (j < width_ - 1) {
            int forward = dataset.GetData().at(current_row).at(j);
            
            int forward_up = dataset.GetData().at(current_row + 1).at(current_column + 1);

            int forward_down = dataset.GetData().at(current_row - 1).at(current_column + 1);

            int current_value = dataset.GetData().at(current_row).at(current_column);
            if (current_row == 0) {
                if (std::abs(current_value - forward) > std::abs(current_value - forward_up)) {
                    current_path.SetLoc(current_column + 1, current_row + 1);
                    current_column++;
                    current_row++;
                    current_path.IncEleChange(static_cast<unsigned int>(std::abs(current_value - forward_up)));
                } else {
                    current_path.SetLoc(current_column + 1, current_row);
                    current_column++;
                    current_path.IncEleChange(static_cast<unsigned int>(std::abs(current_value - forward)));
                }   
            } else if (current_row == height_ - 1) {
                if (std::abs(current_value - forward) > std::abs(current_value - forward_down)) {
                    current_path.SetLoc(current_column + 1, current_row - 1);
                    current_column++;
                    current_row--;
                    current_path.IncEleChange(static_cast<unsigned int>(std::abs()))
                } else {
                    current_path.SetLoc(current_column + 1, current_row);
                    current_column++;
                }
            } else {
                
            }
        }

        