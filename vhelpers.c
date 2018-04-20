
/* Helper to parse version number. */
char *_get_next_vnum(const char *path, char *vnum) {
	// Get the first part of the string, and the last number as a series of tokens
	char *final_token  = malloc(MAX_VNUM_LEN);
	char *tokens[MAX_VNUM_LEN];
	char *vnum_branch = malloc(MAX_VNUM_LEN);

	// Split the tokens by the delimiter .
	int token_i = 0;
	char *res = strtok(vnum, ".");
	if (res != NULL) {
		strcpy(tokens[token_i], res);
		token_i++;
	}

	while ((res = strtok(NULL, ".")) != NULL) {
		strcpy(tokens[token_i], res);
		token_i++;
	}
	strcpy(final_token, tokens[token_i-1]);

	// Build the part of the vnum "branch" before the final delimited number (ie a.b.c.d -> a.b.c.)
	vnum_branch[0] = '\0';
	for(int i = 0; i < token_i; i++) {
		strcat(vnum_branch, tokens[i]);
	}

	// Make the sdir be a directory
	chmod(path, (0755 | S_IFDIR));
	int final_num = atoi(final_token);
	char *final_path = malloc(MAX_VNUM_LEN);
	char *final_num_str = malloc(MAX_VNUM_LEN);
	sprintf(final_num_str, "%d", final_num+1);

	// Increment the current version number by 1.
	strcpy(final_path, path);
	strcat(final_path, "/");
	strcat(final_path, vnum_branch);
	strcat(final_path, (const char *) final_num_str);

	// If there is already a child of the current directory, make a new branch (see Wiki research if this is confusing)
	if (access(final_path, F_OK) != -1) {
		strcpy(final_path, path);
		strcat(final_path, "/");
		strcat(final_path, vnum_branch);
		sprintf(final_num_str, "%d", final_num);
		strcat(final_path, (const char *) final_num_str);
		strcat(final_path, ".1");
		while (access(final_path, F_OK) != -1) {
			final_path[strlen(final_path)-1] = '0';
			strcat(final_path, ".1");
		}
	}

	free(final_token);
	free(res);
	for (int i = 0; i < MAX_VNUM_LEN; i++) {
		free(tokens[i]);
	}
	free(vnum_branch);

	return final_path;
}
