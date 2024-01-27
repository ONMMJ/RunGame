// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffOptionData.h"
#include "Containers/Array.h"

TArray<FOptionInfo> UBuffOptionData::RandomPickupOption(int num)
{
	int maxPerCount = SumPersentCount();
	// ��������
	TArray<FOptionInfo> infoList = static_cast<TArray<FOptionInfo>>(optionList);
	TArray<FOptionInfo> result;
	FOptionInfo temp;
	for (int i = 0; i < num; i++) 
	{
		int sumPerCount = 0;
		int perCount = FMath::RandRange(1, maxPerCount);
		UE_LOG(LogTemp, Warning, TEXT("%d, %d, %d"), infoList.Num(), maxPerCount,perCount);
		for (int j = 0; j<infoList.Num(); j++)
		{
			sumPerCount += infoList[j].persentCount;
			// Ȯ��ī��Ʈ ���� ������ �����̸�
			if (perCount <= sumPerCount)
			{
				result.Add(infoList[j]);
				maxPerCount -= infoList[j].persentCount;
				infoList.RemoveAt(j);
				break;
			}
		}
	}
	int index = FMath::RandRange(0, 4);
	return result;
}

int UBuffOptionData::SumPersentCount()
{
	int sum = 0;
	for (FOptionInfo var : optionList)
	{
		sum += var.persentCount;
	}
	return sum;
}
