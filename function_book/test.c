/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/09/30 02:29:32 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int ft_strequel(const char *s1, const char *s2)
{
	int ix;

	ix = 0;
	while (s1[ix] && s2[ix])
	{
		if (s1[ix] != s2[ix])
			return (1);
		ix++;
	}
	return (0);
}

int fn_strerr(char *errm, size_t errm_len)
{
	write(2, errm, errm_len);
	exit(EXIT_FAILURE);
}

// 매개변수로 받은 파일이 실제로 현재 작업하는 디렉토리 내에 있는지 검색하는 함수
// readdir 로 dirent 구조체를 받아올 때 더 이상 받아올 파일 정보가 없다면 NULL을 반환하기에 탈출 조건으로 성립
// dirent->d_name, 즉 읽어온 파일 정보 구조체의 파일 이름 정보가 매개변수랑 동일하는 지를 체크 
int fn_search_file(const char *file_name, DIR *dirp)
{
	struct dirent		*direntp;

	direntp = readdir(dirp);
	while (direntp != NULL && ft_strequel(direntp->d_name, file_name))
		direntp = readdir(dirp);
	if (direntp == NULL)
		return (1);
	return (0);
}

int is_directory(mode_t st_mode)
{
	return (((st_mode) & S_IFMT) == S_IFDIR);
}

int main(int argc, char *argv[]){
	char		*current_dir;
	struct stat	statbuf;
	DIR			*dirp;

	if (argc != 2)
		fn_strerr("insert a file_name you wanna delete\n", 37);
	// 현재 경로를 받아온 뒤에 opendir로 디렉토리 스트림을 열어준다.
	current_dir = getcwd(NULL, 0);
	dirp = opendir(current_dir);
	// 차례대로 아래의 작업을 하며 에러 체킹을 한다.
	// - 만약 존재하지 않는 파일이면 에러
	// - 만약 stat 함수의 동작이 실패한다면 에러
	// - 해당 경로의 파일 유형이 디렉토리라면 에러
	if (fn_search_file(argv[1], dirp))
		fn_strerr("Error : no file\n", 17);
	if (lstat(argv[1], &statbuf) == -1)
		fn_strerr("Error : unknown file\n", 22);
	if (is_directory(statbuf.st_mode))
		fn_strerr("Error : this is directory\n", 27);
	// 에러처리 이후 실제로 파일을 unlink 해준다.
	// 여기서 해당 파일의 dirent->d_inode 값이 0이 된다면 파일이 삭제된다.
	unlink(argv[1]);
	printf("file : %s was deleted\n", argv[1]);
	// 디렉토리 스트림을 닫아주고, getcwd로 불러와서 힙에 저장한 경로 문자열을 free 해준다.
	closedir(dirp);
	free(current_dir);
	return (0);
}
