< time_total; ++time){
        // 바이러스 객체 별로 1시간 동안의 행위 시작
        vector<Virus> temp_vec;
        for (Virus& v : viruses){
            vector<Virus> bin = v.propagate(is_building,time_delay, grid_row, grid_col, virus_pos, viruses);
            temp_vec.insert(temp_vec.end(),bin.begin(),bin.end());
        }
        viruses.insert(viruses.end(),temp_vec.begin(),temp_vec.end());
    }