sort(viruses.begin(), viruses.end());
    viruses.erase(std::unique(viruses.begin(), viruses.end()), viruses.end());
    