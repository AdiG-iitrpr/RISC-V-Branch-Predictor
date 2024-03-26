#pragma once

enum class BranchState {
	TAKEN,              // 1
	NOT_TAKEN,          // 0
	STRONGLY_TAKEN,       // 11
	WEAKLY_TAKEN,       // 10
	WEAKLY_NOT_TAKEN,   // 01
	STRONGLY_NOT_TAKEN, // 00
	INVALID
};