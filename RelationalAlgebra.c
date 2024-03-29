#include "RelationalAlgebra.h"
#include "TPNRelation.h"
#include "Hashtable.h"



ProjectionTPN newProjectionTPN(char* team) {
    ProjectionTPN newProjectionTPN = malloc(sizeof(struct ProjectionTPN));
    strcpy(newProjectionTPN->Team, team);
    return newProjectionTPN;
}
ProjectionTPNRelation newProjectionTPNRelation(char* key, int capacity) {
    ProjectionTPNRelation newProjectionTPNRelation = malloc(sizeof(struct ProjectionTPNRelation));
    newProjectionTPNRelation->capacity = capacity;
    newProjectionTPNRelation->entries = 0;
    newProjectionTPNRelation->teamHashTable = newHashTable(capacity);

    return newProjectionTPNRelation;
}
bool insertProjectTPN(char* team, ProjectionTPNRelation projectionTPNRelation) {
    // Check if the TPN Tuple already exists in the Relation
    Bucket tupleBucket = lookUpBucket(projectionTPNRelation->teamHashTable, projectionTPNRelation->capacity, team);


    if (!tupleBucket) {

        ProjectionTPN newProTPN = newProjectionTPN(team);

        printf("\nInserting: \n Team: %s associated with ID: %s\n", team, projectionTPNRelation->key);
        // Insert into Team HashTable
        insert(projectionTPNRelation->teamHashTable, team, newProTPN);
        projectionTPNRelation->entries++;

        printf("\n\nDuplicate Doesn't Exist, Insert Successful!\n");
        printf("Entries in TPN Relation: %d\n\n", projectionTPNRelation->entries);

        return true;

    }

    printf("\nInserting: \n Team: %s associated with ID: %s\n", team, projectionTPNRelation->key);
    printf("\n\nDuplicate Exists, Insert Unsuccessful!\n");
    printf("Entries in TPN Relation: %d\n\n", projectionTPNRelation->entries);
    return false;

}


JoinGHVDPG newJoinGHVDPG(char* gameId, char* homeTeam, char* visitorTeam, char* date, char* playerId, char* goals) {
    JoinGHVDPG newJoinGHVDPG = malloc(sizeof(struct JoinGHVDPG));
    strcpy(newJoinGHVDPG->GameId, gameId);
    strcpy(newJoinGHVDPG->HomeTeam, homeTeam);
    strcpy(newJoinGHVDPG->VisitorTeam, visitorTeam);
    strcpy(newJoinGHVDPG->Date, date);
    strcpy(newJoinGHVDPG->PlayerId, playerId);
    strcpy(newJoinGHVDPG->Goals, goals);
    return newJoinGHVDPG;
}
JoinGHVDPGRelation newJoinGHVDPGRelation(int capacity) {
    JoinGHVDPGRelation newJoinGHVDPGRelation = malloc(sizeof(struct JoinGHVDPGRelation));
    newJoinGHVDPGRelation->capacity = capacity;
    newJoinGHVDPGRelation->entries = 0;
    newJoinGHVDPGRelation->gameIdHashTable = newHashTable(capacity);
    newJoinGHVDPGRelation->homeTeamHashTable = newHashTable(capacity);
    newJoinGHVDPGRelation->visitorTeamHashTable = newHashTable(capacity);
    newJoinGHVDPGRelation->dateHashTable = newHashTable(capacity);
    newJoinGHVDPGRelation->playerIdHashTable = newHashTable(capacity);
    newJoinGHVDPGRelation->goalsHashTable = newHashTable(capacity);
    return newJoinGHVDPGRelation;
}
bool insertJoinGHVDPG(char* gameId, char* homeTeam, char* visitorTeam, char* date, char* playerId, char* goals, JoinGHVDPGRelation joinGHVDPGRelation) {
    // Check if the TPN Tuple already exists in the Relation
    Bucket tupleBucket = lookUpBucket(joinGHVDPGRelation->gameIdHashTable, joinGHVDPGRelation->capacity, gameId);

    if(!tupleBucket) {

        // Insert JoinGHVDPG Tuple into Relation
        JoinGHVDPG newJoinGHVDPGTuple = newJoinGHVDPG(gameId, homeTeam, visitorTeam, date, playerId, goals);
        printf("\nInserting: \n GameId: %s\n HomeTeam: %s\n VisitorTeam: %s\n Date: %s\n PlayerId: %s\n Goals: "
               "%s\n", gameId, homeTeam, visitorTeam, date, playerId, goals);

        // Insert into GameId HashTable
        insert(joinGHVDPGRelation->gameIdHashTable, gameId, newJoinGHVDPGTuple);
        // Insert into HomeTeam HashTable
        insert(joinGHVDPGRelation->homeTeamHashTable, homeTeam, newJoinGHVDPGTuple);
        // Insert into VisitorTeam HashTable
        insert(joinGHVDPGRelation->visitorTeamHashTable, visitorTeam, newJoinGHVDPGTuple);
        // Insert into Date HashTable
        insert(joinGHVDPGRelation->dateHashTable, date, newJoinGHVDPGTuple);
        // Insert into PlayerId HashTable
        insert(joinGHVDPGRelation->playerIdHashTable, playerId, newJoinGHVDPGTuple);
        // Insert into Goals HashTable
        insert(joinGHVDPGRelation->goalsHashTable, goals, newJoinGHVDPGTuple);

        joinGHVDPGRelation->entries++;

        printf("\n\nDuplicate Doesn't Exist, Insert Successful!\n");
        printf("Entries in GHVDPG Relation: %d\n\n", joinGHVDPGRelation->entries);

        return true;

    }

    while (tupleBucket) {
        // If all the attributes match, then the tuple already exists in the relation
        JoinGHVDPG joinGHVDPG = tupleBucket->relationTuple;

        if (strcmp(joinGHVDPG->GameId, gameId) == 0 && strcmp(joinGHVDPG->HomeTeam, homeTeam)== 0 &&
            strcmp(joinGHVDPG->VisitorTeam, visitorTeam) == 0 && strcmp(joinGHVDPG->Date, date) == 0 &&
            strcmp(joinGHVDPG->PlayerId, playerId) == 0 && strcmp(joinGHVDPG->Goals, goals) == 0) {

            printf("\n\nDuplicate Exists, Insert Unsuccessful!\n");
            printf("Entries in GHVDPG Relation: %d\n\n", joinGHVDPGRelation->entries);

            return false;
        }

        tupleBucket = tupleBucket->next;
    }

    // Insert JoinGHVDPG Tuple into Relation
    JoinGHVDPG newJoinGHVDPGTuple = newJoinGHVDPG(gameId, homeTeam, visitorTeam, date, playerId, goals);
    printf("\nInserting: \n GameId: %s\n HomeTeam: %s\n VisitorTeam: %s\n Date: %s\n PlayerId: %s\n Goals: "
           "%s\n", gameId, homeTeam, visitorTeam, date, playerId, goals);
    // Insert into GameId HashTable
    insert(joinGHVDPGRelation->gameIdHashTable, gameId, newJoinGHVDPGTuple);
    // Insert into HomeTeam HashTable
    insert(joinGHVDPGRelation->homeTeamHashTable, homeTeam, newJoinGHVDPGTuple);
    // Insert into VisitorTeam HashTable
    insert(joinGHVDPGRelation->visitorTeamHashTable, visitorTeam, newJoinGHVDPGTuple);
    // Insert into Date HashTable
    insert(joinGHVDPGRelation->dateHashTable, date, newJoinGHVDPGTuple);
    // Insert into PlayerId HashTable
    insert(joinGHVDPGRelation->playerIdHashTable, playerId, newJoinGHVDPGTuple);
    // Insert into Goals HashTable
    insert(joinGHVDPGRelation->goalsHashTable, goals, newJoinGHVDPGTuple);

    joinGHVDPGRelation->entries++;

    printf("\n\nDuplicate Doesn't Exist, Insert Successful!\n");
    printf("Entries in GHVDPG Relation: %d\n\n", joinGHVDPGRelation->entries);

    return true;
}


AllofTheAbove newAllofTheAbove(char* playerId, char* goals) {
    AllofTheAbove allofTheAbove = (AllofTheAbove) malloc(sizeof(struct AllofTheAbove));
    strcpy(allofTheAbove->PlayerId, playerId);
    strcpy(allofTheAbove->Goals, goals);
    return allofTheAbove;
}
AllofTheAboveRelation newAllofTheAboveRelation(int capacity) {
    AllofTheAboveRelation allofTheAboveRelation = (AllofTheAboveRelation) malloc(sizeof(struct AllofTheAboveRelation));
    allofTheAboveRelation->capacity = capacity;
    allofTheAboveRelation->entries = 0;
    allofTheAboveRelation->playerIdHashTable = newHashTable(capacity);
    allofTheAboveRelation->goalsHashTable = newHashTable(capacity);
    return allofTheAboveRelation;
}
bool insertAllofTheAbove(char* playerId, char* goals, AllofTheAboveRelation allofTheAboveRelation) {
    Bucket bucket = lookUpBucket(allofTheAboveRelation->playerIdHashTable, allofTheAboveRelation->capacity, playerId);

    if (bucket) {
        while (bucket) {
            AllofTheAbove allofTheAbove = bucket->relationTuple;
            if (strcmp(allofTheAbove->PlayerId, playerId) == 0 && strcmp(allofTheAbove->Goals, goals) == 0) {
                printf("\nDuplicate Exists, Insert Unsuccessful!\n");
                return false;
            }
            bucket = bucket->next;
        }
    }

    AllofTheAbove newAllofTheAboveTuple = newAllofTheAbove(playerId, goals);
    insert(allofTheAboveRelation->playerIdHashTable, playerId, newAllofTheAboveTuple);
    insert(allofTheAboveRelation->goalsHashTable, goals, newAllofTheAboveTuple);
    allofTheAboveRelation->entries++;

    printf("\n\nDuplicate Doesn't Exist, Insert Successful!\n");
    printf("Entries in AllofTheAbove Relation: %d\n\n", allofTheAboveRelation->entries);

    return true;

}


// Select
TPNRelation select_TPN(char* playerID, TPNRelation tpnRelation) {

    Bucket selectedPlayerBucket = lookUpBucket(tpnRelation->playerIDHashTable, tpnRelation->capacity, playerID);

    if (selectedPlayerBucket) {

        TPNRelation selectedPlayerRelation = newTPNRelation(MAX_TABLE_SIZE);

        while (selectedPlayerBucket) {

            TPN tpn = selectedPlayerBucket->relationTuple;

            insert_TPN(tpn->Team, tpn->PlayerId, tpn->Number, selectedPlayerRelation);

            selectedPlayerBucket = selectedPlayerBucket->next;

        }

        return selectedPlayerRelation;
    }

    else {
        return NULL;
    }

}
// Project
ProjectionTPNRelation project_TPN(char* playerID, TPNRelation tpnRelation) {

    TPNRelation selectedPlayerRelation = select_TPN(playerID, tpnRelation);
    Bucket selectedPlayerBucket = lookUpBucket(selectedPlayerRelation->playerIDHashTable, selectedPlayerRelation->capacity, playerID);

    if (selectedPlayerBucket) {

        ProjectionTPNRelation projectionTPNRelation = newProjectionTPNRelation(playerID, MAX_TABLE_SIZE);

        while (selectedPlayerBucket) {

            TPN tpn = selectedPlayerBucket->relationTuple;

            insertProjectTPN(tpn->Team, projectionTPNRelation);

            selectedPlayerBucket = selectedPlayerBucket->next;

        }

        return projectionTPNRelation;
    }

    else {
        return NULL;
    }
}
// Join
JoinGHVDPGRelation join_GHVDPG(GHVDRelation ghvdRelation, GPGRelation gpgRelation) {

    JoinGHVDPGRelation newJoinRelation = newJoinGHVDPGRelation(MAX_TABLE_SIZE);
    HashTable ghvdHashTable = ghvdRelation->gameIdHashTable;
    HashTable gpgHashTable = gpgRelation->gameIdHashTable;

    for (int i = 0; i < ghvdRelation->capacity; i++) {

        Bucket ghvdRelationBucket = ghvdHashTable->table[i];

        if (ghvdRelationBucket) {
            GHVD ghvdTuple = ghvdRelationBucket->relationTuple;
            Bucket gpgBucket = lookUpBucket(gpgHashTable, gpgRelation->capacity, ghvdTuple->GameId);

            if (gpgBucket) {
                while (gpgBucket) {
                    GPG gpgTuple = gpgBucket->relationTuple;
                    insertJoinGHVDPG(ghvdTuple->GameId, ghvdTuple->HomeTeam, ghvdTuple->VisitorTeam, ghvdTuple->Date, gpgTuple->PlayerId, gpgTuple->Goals, newJoinRelation);

                    gpgBucket = gpgBucket->next;
                }
            }

            else {
                insertJoinGHVDPG(ghvdTuple->GameId, ghvdTuple->HomeTeam, ghvdTuple->VisitorTeam, ghvdTuple->Date, "-", "-", newJoinRelation);
            }

        }
    }

    return newJoinRelation;
}

// All of the Above
// Takes in a date and a join relation
// Selects Tuples from the join relation that have the same date
// Projects the selected tuples to get the playerID and goals
AllofTheAboveRelation relational_all_of_the_above(char* date, JoinGHVDPGRelation joinGHVDPGRelation) {

    AllofTheAboveRelation allofTheAboveRelation = newAllofTheAboveRelation(MAX_TABLE_SIZE);
    HashTable JoinedHashTable = joinGHVDPGRelation->playerIdHashTable;

    // Run a for loop on the joinGHVDPGRelation->playerIdHashTable->table
    // Check if the date is the same as the date in the tuple
    // If yes insert it into the allofTheAboveRelation

    for (int i = 0; i < joinGHVDPGRelation->capacity; i++) {

        Bucket joinGHVDPGBucket = JoinedHashTable->table[i];

        if (joinGHVDPGBucket) {
            while (joinGHVDPGBucket) {
                JoinGHVDPG joinGHVDPG = joinGHVDPGBucket->relationTuple;
                if (strcmp(joinGHVDPG->Date, date) == 0) {
                    insertAllofTheAbove(joinGHVDPG->PlayerId, joinGHVDPG->Goals, allofTheAboveRelation);
                }
                joinGHVDPGBucket = joinGHVDPGBucket->next;
            }

        }
    }

    if (allofTheAboveRelation->entries == 0) {
        return NULL;
    }

    return allofTheAboveRelation;

}



void printAllofTheAbove(Bucket allofTheAbove) {
    AllofTheAbove allofTheAboveTuple = allofTheAbove->relationTuple;
    printf("Tuple Address: %p \n", allofTheAboveTuple);
    printf("\n PlayerId: %s \n", allofTheAboveTuple->PlayerId);
    printf("\n Goals: %s \n", allofTheAboveTuple->Goals);
}
void printAllofTheAboveRelation(AllofTheAboveRelation allofTheAboveRelation) {

    for (int i = 0; i < allofTheAboveRelation->capacity; i++) {
        Bucket allofTheAboveBucket = allofTheAboveRelation->playerIdHashTable->table[i];
        if (allofTheAboveBucket) {
            while (allofTheAboveBucket) {
                printAllofTheAbove(allofTheAboveBucket);
                allofTheAboveBucket = allofTheAboveBucket->next;
            }
        }
    }

}
void freeAllofTheAboveRelation(AllofTheAboveRelation allofTheAboveRelation) {

    for (int i = 0; i < allofTheAboveRelation->capacity; i++) {
        Bucket allofTheAboveBucket = allofTheAboveRelation->playerIdHashTable->table[i];
        if (allofTheAboveBucket) {
            while (allofTheAboveBucket) {
                free(allofTheAboveBucket->relationTuple);
                allofTheAboveBucket = allofTheAboveBucket->next;
            }
        }
    }

    freeHashTable(allofTheAboveRelation->playerIdHashTable);
    freeHashTable(allofTheAboveRelation->goalsHashTable);
    free(allofTheAboveRelation);

}
void freeAllofTheAbove(AllofTheAbove allofTheAbove) {
    free(allofTheAbove);
}

void printJoinGHVDPG(Bucket joinGHVDPG) {
    JoinGHVDPG joinGHVDPGTuple = joinGHVDPG->relationTuple;
    printf("Tuple Address: %p \n", joinGHVDPGTuple);
    printf("\n GameId: %s \n", joinGHVDPGTuple->GameId);
    printf("\n HomeTeam: %s \n", joinGHVDPGTuple->HomeTeam);
    printf("\n VisitorTeam: %s \n", joinGHVDPGTuple->VisitorTeam);
    printf("\n Date: %s \n", joinGHVDPGTuple->Date);
    printf("\n PlayerId: %s \n", joinGHVDPGTuple->PlayerId);
    printf("\n Goals: %s \n", joinGHVDPGTuple->Goals);
}
void printJoinGHVDPGRelation(JoinGHVDPGRelation joinGHVDPGRelation) {
    HashTable table = joinGHVDPGRelation->gameIdHashTable;
    printf("\n\nPrinting JoinGHVDPG Relation Tuples:\n");
    printf("\nEntries in JoinGHVDPG Relation: %d\n\n", joinGHVDPGRelation->entries);
    for (int i = 0; i < table->capacity; i++) {
        Bucket current = table->table[i];
        while (current != NULL) {
            printJoinGHVDPG(current);
            current = current->next;
        }
    }
}
void freeJoinGHVDPGRelation(JoinGHVDPGRelation joinGHVDPGRelation) {

    HashTable table = joinGHVDPGRelation->gameIdHashTable;
    for (int i = 0; i < table->capacity; i++) {
        Bucket current = table->table[i];
        while (current != NULL) {
            freeJoinGHVDPG(current->relationTuple);
            current = current->next;
        }
    }
    freeHashTable(table);
    freeHashTable(joinGHVDPGRelation->homeTeamHashTable);
    freeHashTable(joinGHVDPGRelation->visitorTeamHashTable);
    freeHashTable(joinGHVDPGRelation->dateHashTable);
    freeHashTable(joinGHVDPGRelation->playerIdHashTable);
    freeHashTable(joinGHVDPGRelation->goalsHashTable);
    free(joinGHVDPGRelation);
}
void freeJoinGHVDPG(JoinGHVDPG joinGHVDPG) {
    free(joinGHVDPG);
}

void printProjectedTNP(Bucket bucketPointer) {
    ProjectionTPN projectedTuple = (ProjectionTPN) bucketPointer->relationTuple;
    printf("Tuple Address: %p \n", projectedTuple);
    printf("\n Team: %s \n", projectedTuple->Team);

}
void printProjectedTPN(ProjectionTPNRelation relation) {
    HashTable table = relation->teamHashTable;
    printf("\n\nPrinting Projected Relation Tuples for Player ID %s:\n", relation->key);
    printf("\nEntries in Projected Relation: %d\n\n", table->entries);
    for (int i = 0; i < table->capacity; i++) {
        Bucket current = table->table[i];
        while (current != NULL) {
            printf("\nEntry at Index: %d\n", i);
            printProjectedTNP(current);
            current = current->next;
        }
    }
}
void freeProjectedTPNRelation(ProjectionTPNRelation tpnProjectedrelation) {

    // Free the Bucket->Value
    HashTable hashTable = tpnProjectedrelation->teamHashTable;
    for (int i = 0; i < tpnProjectedrelation->capacity; i++) {

        Bucket bucket = hashTable->table[i];

        while (bucket != NULL) {
            if(bucket->relationTuple != NULL) {
                free((ProjectionTPN) bucket->relationTuple);
            }
            bucket = bucket->next;
        }
    }

    freeHashTable(hashTable);
    free(tpnProjectedrelation);
}