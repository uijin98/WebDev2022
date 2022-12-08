using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameDirector : MonoBehaviour
{

    GameObject timerText;
    GameObject PointText;
    float time = 60.0f; //60�� ���� ���� ����
    int point = 0;

  
    public void Gethalf()
    {
        this.point /= 2;

    }
   
    public void Gettangerine()
    {
        this.point /= 2;

    }
    public void Getcoke()
    {
        this.point += 100;

    }

    public void Getskeleton()
    {
        this.point += 100;
    }
    public void Getsoda()
    {
        this.point += 100;
    }



    // Use this for initialization
    void Start()
    {
        this.timerText = GameObject.Find("Time");
        this.PointText = GameObject.Find("Point");
    }

    // Update is called once per frame
    void Update()
    {
        // �� �������� �ð����� time���� ����.
        this.time -= Time.deltaTime;
        // F1 ���� �����ڸ� ����� ǥ���Ѵ�.
        this.timerText.GetComponent<Text>().text = this.time.ToString("F1");
        this.PointText.GetComponent<Text>().text = this.point.ToString() + " point";
    }
}