cmake_minimum_required(VERSION 3.20)
project(GradeAnalysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(GradeAnalysis main.cpp AnswerSheet.cpp AnswerSheet.h Concept.cpp Concept.h GradeAnalysis.cpp GradeAnalysis.h Question.cpp Question.h Quiz.cpp Quiz.h ReadHelper.cpp ReadHelper.h Student.cpp Student.h UsefulTools.cpp UsefulTools.h)
