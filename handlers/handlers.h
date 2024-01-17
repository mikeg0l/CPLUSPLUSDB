#pragma once

#include "../database/database.h"


void handleCreateTable(Database& db, std::istringstream& iss);
void handleAddColumn(Database& db, std::istringstream& iss);
void handleDeleteTable(Database& db, std::istringstream& iss);
void handleDeleteRow(Database& db, std::istringstream& iss);
void handleSave(Database& db, std::istringstream& iss);
void handleLoad(Database& db, std::istringstream& iss);
void handleInsert(Database& db, std::istringstream& iss);
void handleUpdate(Database& db, std::istringstream& iss);
void handleList(Database& db, std::istringstream& iss);
void handleDisplay(Database& db, std::istringstream& iss);